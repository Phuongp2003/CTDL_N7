#include "../header/hanhkhach.h"
#include "../header/queue.h"

HanhKhach::HanhKhach() : cmnd(""), ho(""), ten(""), phai(-1) {}

HanhKhach::HanhKhach(string cmnd, string ho, string ten, int phai)
{
	this->cmnd = cmnd;
	this->ho = ho;
	this->ten = ten;
	this->phai = phai;
}

string HanhKhach::getCmnd() { return this->cmnd; }

string HanhKhach::getHo() { return this->ho; }

string HanhKhach::getTen() { return this->ten; }

string HanhKhach::getPhai()
{
	return phai == 0 ? "Nam" : "Nu";
}

void HanhKhach::setCmnd(string cmnd) { this->cmnd = cmnd; }

void HanhKhach::setHo(string ho) { this->ho = ho; }

void HanhKhach::setTen(string ten) { this->ten = ten; }

void HanhKhach::setPhai(int phai) { this->phai = phai; }

//------------------------------------------------------------

NodeHK::NodeHK() {}

NodeHK::NodeHK(HanhKhach hanhKhach)
{
	this->hanhKhach = hanhKhach;
	this->left = NULL;
	this->right = NULL;
}

HanhKhach NodeHK::getHK() { return this->hanhKhach; }

NodeHK *NodeHK::getLeft() { return this->left; }

NodeHK *NodeHK::getRight() { return this->right; }

void NodeHK::setHK(HanhKhach hanhKhach) { this->hanhKhach = hanhKhach; }

void NodeHK::setLeft(NodeHK *left) { this->left = left; }

void NodeHK::setRight(NodeHK *right) { this->right = right; }

//------------------------------------------------------------

DsHanhKhach::DsHanhKhach()
{
	this->root = NULL;
	this->size = 0;
}

void DsHanhKhach::deleteDs(NodeHK *node)
{
	if (node == NULL)
	{
		return;
	}
	deleteDs(node->getLeft());
	deleteDs(node->getRight());
	delete node;
	node = NULL;
}

void DsHanhKhach::deleteDs()
{
	deleteDs(root);
}

void DsHanhKhach::insert(HanhKhach hanhKhach)
{
	if (root == NULL)
	{
		root = new NodeHK(hanhKhach);
		size++;
		return;
	}

	NodeHK *current = root;
	while (true)
	{
		if (stoi(hanhKhach.getCmnd()) < stoi(current->getHK().getCmnd()))
		{
			if (current->getLeft() == NULL)
			{
				current->setLeft(new NodeHK(hanhKhach));
				size++;
				break;
			}
			else
			{
				current = current->getLeft();
			}
		}
		else if (stoi(hanhKhach.getCmnd()) >
				 stoi(current->getHK().getCmnd()))
		{
			if (current->getRight() == NULL)
			{
				current->setRight(new NodeHK(hanhKhach));
				size++;
				break;
			}
			else
			{
				current = current->getRight();
			}
		}
		else
		{
			current = NULL;
			break;
		}
	}
}

NodeHK *DsHanhKhach::search(NodeHK *&prevNode, string cmnd)
{
	NodeHK *current = root;

	while (current != NULL)
	{
		if (cmnd.compare(current->getHK().getCmnd()) == 0)
		{
			return current;
		}
		else if (stoi(cmnd) < stoi(current->getHK().getCmnd()))
		{
			prevNode = current;
			current = current->getLeft();
		}
		else
		{
			prevNode = current;
			current = current->getRight();
		}
	}
	return NULL;
}

NodeHK *DsHanhKhach::search(string cmnd)
{
	if (root == NULL)
	{
		return NULL;
	}

	NodeHK *prevNode = NULL;
	return search(prevNode, cmnd);
}

void DsHanhKhach::writeToFileOneHK(NodeHK *node)
{
	ofstream file;
	file.open("../data/dataHK.txt", ios::out | ios::app);
	if (!file.is_open())
	{
		return;
	}

	HanhKhach hanhKhach = node->getHK();
	string phai = (hanhKhach.getPhai() == "Nam") ? "0" : "1";
	file << hanhKhach.getCmnd() << '|' << hanhKhach.getHo() << '|'
		 << hanhKhach.getTen() << '|' << phai << "|\n";
	file.close();
}

void DsHanhKhach::writeToFileAllHK()
{
	ofstream file;
	file.open("../data/dataHK.txt", ios::out);

	if (!file.is_open() || root == NULL)
	{
		return;
	}

	NodeHK *currNode;
	Queue queue;
	string phai;
	queue.push(root);

	while (!queue.isEmpty())
	{
		currNode = queue.getFront();
		queue.pop();
		phai = (currNode->getHK().getPhai() == "Nam") ? "0" : "1";
		file << currNode->getHK().getCmnd() << '|' << currNode->getHK().getHo() << '|'
			 << currNode->getHK().getTen() << '|' << phai << "|\n";

		if (currNode->getLeft() != NULL)
		{
			queue.push(currNode->getLeft());
		}
		if (currNode->getRight() != NULL)
		{
			queue.push(currNode->getRight());
		}
	}

	file.close();
}

void DsHanhKhach::readFromFile()
{
	ifstream file;
	file.open("../data/dataHK.txt", ios::in);
	if (!file.is_open())
	{
		return;
	}

	string line;
	string cmnd, ho, ten, phai;
	while (getline(file, line))
	{
		stringstream ss(line);
		getline(ss, cmnd, '|');
		getline(ss, ho, '|');
		getline(ss, ten, '|');
		getline(ss, phai, '|');
		insert(HanhKhach(cmnd, ho, ten, stoi(phai)));
	}
	file.close();
}

int DsHanhKhach::getSize() { return this->size; }

NodeHK *DsHanhKhach::getRoot() { return this->root; }

NodeHK *DsHanhKhach::minLeftNode(NodeHK *node)
{
	while (node->getLeft() != NULL)
	{
		node = node->getLeft();
	}
	return node;
}

void DsHanhKhach::remove(NodeHK *node)
{
	NodeHK *prevNode = NULL;

	// Lấy node cha của node cần xóa
	search(prevNode, node->getHK().getCmnd());

	if (node == NULL)
	{
		return;
	}

	// Trường hợp 1: node cần xóa là nút lá
	if (node->getLeft() == NULL && node->getRight() == NULL)
	{
		if (node != root)
		{
			if (prevNode->getLeft() == node)
			{
				prevNode->setLeft(NULL);
			}
			else
			{
				prevNode->setRight(NULL);
			}
		}
		else
			root = NULL;

		delete node;
		node = NULL;
	}

	// Trường hợp 2: node cần xóa có 2 con
	else if (node->getLeft() != NULL && node->getRight() != NULL)
	{
		// Node thay thế cho node cần xóa
		NodeHK *minNode = minLeftNode(node->getRight());

		// Lưu dữ liệu của node thay thế
		HanhKhach minHK = minNode->getHK();

		remove(minNode);

		// Ghì đè dữ liệu của node thay thế lên node cần xóa
		node->setHK(minHK);
	}

	// Trường hợp 3: node cần xóa có 1 con
	else
	{
		NodeHK *child = (node->getLeft() != NULL)
							? node->getLeft()
							: node->getRight();

		if (node != root)
		{
			if (node == prevNode->getLeft())
			{
				prevNode->setLeft(child);
			}
			else
			{
				prevNode->setRight(child);
			}
		}
		else
		{
			root = child;
		}

		delete node;
		node = NULL;
	}
}
