/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
private:
    struct node {
    	value_type value;
		int height;
    	struct node *lchild，*rchild;
    	int ltag, rtag;
	};
	typedef struct node node_t;
    typedef struct node* nodeptr_t;
    nodeptr_t root_;
    long long value_size_;

    nodeptr_t pred(const nodeptr_t node) {
    	if (node->ltag == 1 || node->lchild == NULL)
    		return node->lchild;
    	nodeptr_t temp = node->lchild;
    	while (temp->rtag == 0)
    		temp = temp->rchild;
    	return temp;
    }

    nodeptr_t succ(const nodeptr_t node) {
    	if (node->rtag == 1 || node->rchild == NULL)
    		return node->rchild;
    	nodeptr_t temp = node->rchild;
    	while (temp->ltag == 0)
    		temp = temp->lchild;
    	return temp;
    }
public:
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.begin(); --it;
	 *       or it = map.end(); ++end();
	 */
	class const_iterator;
	class iterator {
	private:
		nodeptr_t node_;
	public:
		iterator(nodeptr_t node) : node_(node) {}
		iterator(const iterator &other) : node_(other.node()) {}
		/**
		 * iter++
		 */
		iterator operator++(int) {
			iterator orig(*this);
			node_ = succ(node_);
			return orig;	

		}
		/**
		 * ++iter
		 */
		iterator & operator++() {
        	node_ = succ(node_);
			return (*this);
		}
		/**
		 * iter--
		 */
		iterator operator--(int) {
			iterator orig(*this);
			node_ = pred(node_);
			return orig;
		}
		/**
		 * --iter
		 */
		iterator & operator--() {
			node_ = pred(node_);
			return (*this);
		}
		value_type & operator*() const {
			return node_->value;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {
			return node_ == rhs.node();
		}
		bool operator==(const const_iterator &rhs) const {
			return node_ == rhs.node();
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
   			return node_ != rhs.node();
		}
		bool operator!=(const const_iterator &rhs) const {
			return node_ != rhs.node();
		}
		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept { // ？noexcept
			return &(node_->value);
		}
		const nodeptr_t node() {
			return node_;
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
			// data members.
		public:
			const_iterator() {
				// TODO
			}
			const_iterator(const const_iterator &other) {
				// TODO
			}
			const_iterator(const iterator &other) {
				// TODO
			}
			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.
	};
	/**
	 * two constructors
	 */
	map() : value_size_(0), root(NULL), head(NULL), tail(NULL) {}
	map(const map &other) : value_size_(other.size()) {
		// TODO
	}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {}
	/**
	 * TODO Destructors
	 */
	~map() {}
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key) {}
	const T & at(const Key &key) const {}
	/**
	 * TODO
	 * access specified element 
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const {}
	/**
	 * return a iterator to the beginning
	 */
	iterator begin() {}
	const_iterator cbegin() const {}
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end() {}
	const_iterator cend() const {}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const {
		return value_size_ == 0;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {
		return value_size_;
	}
	/**
	 * clears the contents
	 */
	void clear() {
		post_order_clear(root);
		// map(); ?
	}
	void post_order_clear(nodeptr_t root) {
    	if (root != NULL) {
        	post_order_clear(root->left);
        	post_order_clear(root->right);
        	free(root);
    	}
	}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) {}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) {}
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) {}
	const_iterator find(const Key &key) const {}
};

}

#endif
