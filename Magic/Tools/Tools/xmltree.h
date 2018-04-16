#pragma once

#include "xmlnode.h"
#include <vector>

template <typename T1, typename T2>
class XMLTree : public XMLNode<T1,T2> {
	private:
		static int						nodeId;
		int								level;
		T1								key;
		T2								value;
		int								errors;
		int								warnings;

		// Duplicate Trees and Nodes are allowed
		std::vector<XMLTree<T1, T2>*>	nextLevel;

		// Recursive Helper Functions
		void							getNodesRecursive(XMLNode<T1,T2>* nextNode, std::vector<std::pair<T1, T2>> &traverse);
		void							addNodeRecursive(XMLNode<T1, T2>* nextNode, T1 key, T2 value);

	public:
		XMLTree();
		XMLTree(int level, T1 key, T2 value = {});

		virtual ~XMLTree();

		// Getters
		static int						getNodeId();
		int								getLevel() const;
		T1								getTreeKey() const;
		T2								getTreeValue() const;
		int								getErrors() const;
		int								getWarnings() const;
		bool							isEmpty() const;
		std::vector<XMLTree<T1, T2>*>	getTrees();
		std::vector<std::pair<T1, T2>>	getNodes();
		
		// Setters
		void							setLevel(int level);
		void							setTreeKey(T1 key);
		void							setTreeValue(T2 value);
		void							setErrors(int errors);
		void							setWarnings(int warnings);
		bool							addTree(XMLTree<T1, T2>* tree);
		void							addNode(T1 key, T2 value);
};
