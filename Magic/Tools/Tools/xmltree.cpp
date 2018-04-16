#include "xmltree.h"

// Prevent error LNK2001 : unresolved external symbol static int
template <typename T1, typename T2>
int XMLTree<T1, T2>::nodeId = 0;

template <typename T1, typename T2>
XMLTree<T1, T2>::XMLTree() : XMLNode<T1, T2>() {
	level			= 0;
	errors			= 0;
	warnings		= 0;
}

template <typename T1, typename T2>
XMLTree<T1, T2>::XMLTree(int level, T1 key, T2 value) : XMLNode<T1,T2>() {
	this->level				= level;
	this->key				= key;
	this->value				= value;
	errors					= 0;
	warnings				= 0;
}

template <typename T1, typename T2>
XMLTree<T1, T2>::~XMLTree() {
}

/*
 * Recursive Helper Functions
 */

template <typename T1, typename T2>
void XMLTree<T1, T2>::getNodesRecursive(XMLNode<T1, T2>* nextNode, std::vector<std::pair<T1, T2>> &traverse) {

	if (nextNode != nullptr) {
		// If the Node is a subtree (not a parent Node object) pass it on
		if (!dynamic_cast<XMLNode<T1, T2>*>(nextNode)) {
			getNodesRecursive(nextNode, traverse);
		}
		else {
			// Recursively traverse the left (previous) subtree
			getNodesRecursive(nextNode->getPrevNode(), traverse);

			traverse.push_back(std::make_pair(nextNode->getNodeKey(), nextNode->getNodeValue()));

			// Recursively traverse the right (next) subtree
			getNodesRecursive(nextNode->getNextNode(), traverse);
		}
	}
}

template <typename T1, typename T2>
void XMLTree<T1, T2>::addNodeRecursive(XMLNode<T1, T2>* nextNode, T1 key, T2 value) {
	// Get the next Node key
	T1 nextNodeKey = nextNode->getNodeKey();

	// Recursively check if key is equal to the next Node key or comes before it
	if (key <= nextNodeKey) {
		XMLNode<T1, T2>* newNode = nextNode->getPrevNode();

		if (newNode == nullptr) {
			// Add the new Node to the next Node
			XMLNode<T1, T2>* node = new XMLNode<T1, T2>(key, value);
			nextNode->setPrevNode(node);
		}
		else {
			addNodeRecursive(newNode, key, value);
		}
	}
	// Key must come after the root Node key. Recursively check.
	else {
		XMLNode<T1, T2>* newNode = nextNode->getNextNode();

		if (newNode == nullptr) {
			// Add the new Node to the next Node
			XMLNode<T1, T2>* node = new XMLNode<T1, T2>(key, value);
			nextNode->setNextNode(node);
		}
		else {
			addNodeRecursive(newNode, key, value);
		}
	}
}

/*
* Getters
*/

template <typename T1, typename T2>
int XMLTree<T1, T2>::getNodeId() {
	// Increment, then return the new Node id
	return ++nodeId;
}

template <typename T1, typename T2>
int	XMLTree<T1, T2>::getLevel() const {
	return level;
}

template <typename T1, typename T2>
T1 XMLTree<T1, T2>::getTreeKey() const {
	return key;
}

template <typename T1, typename T2>
T2 XMLTree<T1, T2>::getTreeValue() const {
	return value;
}

template <typename T1, typename T2>
int XMLTree<T1, T2>::getErrors() const {
	return errors;
}

template <typename T1, typename T2>
int XMLTree<T1, T2>::getWarnings() const {
	return warnings;
}

template <typename T1, typename T2>
bool XMLTree<T1, T2>::isEmpty() const {
	return nextLevel.empty() && XMLNode<T1, T2>::isNodeEmpty();
}

template <typename T1, typename T2>
std::vector<XMLTree<T1, T2>*> XMLTree<T1, T2>::getTrees() {
	return nextLevel;
}

template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> XMLTree<T1, T2>::getNodes() {
	std::vector<std::pair<T1, T2>> traverse;

	// Recursively begin at the tree root Node
	getNodesRecursive(this, traverse);

	return traverse;
}

/*
* Setters
*/

template <typename T1, typename T2>
void XMLTree<T1, T2>::setLevel(int level) {
	this->level = level;
}

template <typename T1, typename T2>
void XMLTree<T1, T2>::setTreeKey(T1 key) {
	this->key = key;
}

template <typename T1, typename T2>
void XMLTree<T1, T2>::setTreeValue(T2 value) {
	this->value = value;
}

template <typename T1, typename T2>
void XMLTree<T1, T2>::setErrors(int errors) {
	this->errors = errors;
}

template <typename T1, typename T2>
void XMLTree<T1, T2>::setWarnings(int warnings) {
	this->warnings = warnings;
}

template <typename T1, typename T2>
bool XMLTree<T1, T2>::addTree(XMLTree<T1, T2>* tree) {
	bool added = false;

	if (tree->getLevel() == this->level + 1) {
		nextLevel.push_back(tree);
		added = true;
	}

	return added;
}

template <typename T1, typename T2>
void XMLTree<T1, T2>::addNode(T1 key, T2 value) {
	// Get the root Node key
	T1 rootNodeKey = XMLNode<T1,T2>::getNodeKey();

	// Save key and value in root Node if empty
	if (XMLNode<T1, T2>::isNodeEmpty()) {
		XMLNode<T1, T2>::setNodeKey(key);
		XMLNode<T1, T2>::setNodeValue(value);
	}
	// Recursively check if key is equal to the root Node key or comes before it
	else if (key <= rootNodeKey) {
		XMLNode<T1, T2>* newNode = XMLNode<T1, T2>::getPrevNode();

		if (newNode == nullptr) {
			// Add the new Node to the root Node
			XMLNode<T1, T2>* node = new XMLNode<T1, T2>(key, value);
			XMLNode<T1, T2>::setPrevNode(node);
		}
		else {
			addNodeRecursive(newNode, key, value);
		}
	}
	// Key must come after the root Node key. Recursively check.
	else {
		XMLNode<T1, T2>* newNode = XMLNode<T1, T2>::getNextNode();

		if (newNode == nullptr) {
			// Add the new Node to the root Node
			XMLNode<T1, T2>* node = new XMLNode<T1, T2>(key, value);
			XMLNode<T1, T2>::setNextNode(node);
		}
		else {
			addNodeRecursive(newNode, key, value);
		}
	}
}
