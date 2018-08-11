#include <iostream>

struct Node {

	public:
		int data;
		int count;

		Node *left;
		Node *right;

	Node() {

		data = 0;
		count = 0;

		left = nullptr;
		right = nullptr;
	}

	~Node() {

		delete left;
		delete right;
	}
};

int max(Node *nodeRoot) {

	while (nodeRoot->right != nullptr)
		nodeRoot = nodeRoot->right;

	return nodeRoot->data;
}

void printInOrder(Node *nodeRoot) {

	if (nodeRoot != nullptr) {

		printInOrder(nodeRoot->left);
		std::cout << nodeRoot->data << " ";
		printInOrder(nodeRoot->right);
	}
}

Node *findMin(Node *nodeRoot) {

	while (nodeRoot->left != nullptr)
		nodeRoot = nodeRoot->left;

	return nodeRoot;
}

Node *newNode(int value) {

	Node *newNode = new Node();
	newNode->data = value;
	newNode->count = 1;
	newNode->left = nullptr;
	newNode->right = nullptr;

	return newNode;
}

Node *append(Node *nodeRoot, int value) {

	if (nodeRoot == nullptr)
		nodeRoot = newNode(value);
	else if (value > nodeRoot->data)
		nodeRoot->right = append(nodeRoot->right, value);
	else if (value < nodeRoot->data)
		nodeRoot->left = append(nodeRoot->left, value);
	else if (value == nodeRoot->data)
		nodeRoot->count++;

	return nodeRoot;
}

Node *terminate(Node *nodeRoot, int value) {

	if (nodeRoot == nullptr)
		return nullptr;
	else if (value > nodeRoot->data)
		nodeRoot->right = terminate(nodeRoot->right, value);
	else if (value < nodeRoot->data)
		nodeRoot->left = terminate(nodeRoot->left, value);
	else {
		if (nodeRoot->count > 1) {

			nodeRoot->count--;
		}
		else if (nodeRoot->left == nullptr && nodeRoot->right == nullptr) {

			nodeRoot = nullptr;
			delete nodeRoot;
		}
		else if (nodeRoot->left == nullptr) {

			Node *temp = nodeRoot;
			nodeRoot = nodeRoot->right;
			delete temp;
		}
		else if (nodeRoot->right == nullptr) {

			Node *temp = nodeRoot;
			nodeRoot = nodeRoot->left;
			delete temp;
		}
		else {

			Node *temp = findMin(nodeRoot->right);
			nodeRoot->data = temp->data;
			nodeRoot->right = terminate(nodeRoot->right, temp->data);
		}
	}

	return nodeRoot;
}

int search(Node *nodeRoot, int value) {

	if (nodeRoot == nullptr)
		return 0;
	else if (value == nodeRoot->data)
		return nodeRoot->count;
	else if (value > nodeRoot->data)
		return search(nodeRoot->right, value);
	else if (value < nodeRoot->data)
		return search(nodeRoot->left, value);

}

int main() {

	Node *root = nullptr;

	int nrOfInputs = 0;
	std::cin >> nrOfInputs;

	for (size_t i = 0; i < nrOfInputs; i++) {

		int action = 0;
		std::cin >> action;

		if (action == 0) {

			int number = 0;
			std::cin >> number;

			if (root != nullptr)
				root = terminate(root, number);
			else
				std::cout << "You can not delete empty BST" << std::endl;
		}
		else if (action == 1) {

			int number = 0;
			std::cin >> number;

			root = append(root, number);
		}
		else if (action == 2) {

			int number = 0;
			std::cin >> number;

			int instances = search(root, number);
			if (instances) {
				if (instances > 1)
					std::cout << "There are " << instances << " instances of it in BST" << std::endl;
				else
					std::cout << "There is " << instances << " instance of it in BST" << std::endl;
			}
			else
				std::cout << "Searched number is NOT in BST" << std::endl;
		}
		else if (action == 3) {

			if (root != nullptr)
				std::cout << "The smallest number in BST is " << findMin(root)->data << std::endl;
			else
				std::cout << "The BST is empty" << std::endl;
		}
		else if (action == 4) {

			if (root != nullptr)
				std::cout << "The biggest number in BST is " << max(root) << std::endl;
			else
				std::cout << "The BST is empty" << std::endl;
		}
		else if (action == 5) {

			if (root != nullptr) {

				printInOrder(root);
				std::cout << std::endl;
			}
			else
				std::cout << "The BST is empty" << std::endl;
		}
		else if (action == 99) {

			root->~Node();
			return 0;
		}
	}

	system("PAUSE");
	return 0;
}