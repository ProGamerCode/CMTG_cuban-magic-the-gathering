#pragma once

// Class forwarding
template <typename T1, typename T2>
class XMLTree;

template <typename T1, typename T2>
class XMLNode {
	private:
		int								id;
		T1								key;
		T2								value;
		bool							empty;

		XMLNode<T1, T2>*				prevNode;
		XMLNode<T1, T2>*				nextNode;

	public:
		XMLNode();
		XMLNode(T1 key, T2 value);

		virtual ~XMLNode();

		// Getters
		int					getId() const;
		T1					getNodeKey() const;
		T2					getNodeValue() const;
		bool				isNodeEmpty() const;
		XMLNode<T1, T2>*	getPrevNode() const;
		XMLNode<T1, T2>*	getNextNode() const;

		// Setters
		void				setNodeKey(T1 key);
		void				setNodeValue(T2 value);
		void				setPrevNode(XMLNode<T1, T2>* prevNode);
		void				setNextNode(XMLNode<T1, T2>* nextNode);
};
