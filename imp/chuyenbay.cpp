#include "../header/chuyenbay.h"
using namespace std;

// hàm của ChuyenBay

ChuyenBay::ChuyenBay()
{
	strcpy(maCB, "");
	ngayGio = Date(1, 1, 1991, 0, 0);
	noiDen = "";
}

ChuyenBay::ChuyenBay(const char *maCB, string noiDen, Date ngayGio,
					 const char *maMayBay)
{
	strcpy(this->maCB, maCB);
	strcpy(this->idMayBay, maMayBay);
	this->ngayGio = ngayGio;
	this->noiDen = noiDen;
	this->trangThai = ConVe;
	this->dsVe = *(new DsVeMayBay());
}

char *ChuyenBay::getMaCB() { return this->maCB; }

string ChuyenBay::getNoiDen() { return this->noiDen; }

Date ChuyenBay::getNgayGio() { return this->ngayGio; }

void ChuyenBay::setTrangThai(int trangThai) { this->trangThai = trangThai; }

void ChuyenBay::setidMayBay(const char *idMayBay)
{
	strcpy(this->idMayBay, idMayBay);
}

int ChuyenBay::getTrangThai() { return this->trangThai; }

const char *ChuyenBay::getMaMayBay() { return this->idMayBay; }

void ChuyenBay::setNgayGio(Date ngayGio) { this->ngayGio = ngayGio; }

bool ChuyenBay::checkNoiDen(const char *noiDen)
{
	if (isGotStr(this->noiDen, noiDen))
		return true;
	return false;
}

bool ChuyenBay::checkTime(Date time)
{
	if (ngayGio == time)
		return true;
	return false;
}

bool ChuyenBay::checkMaCB(const char *maCB)
{
	if (isGotStr(this->maCB, maCB))
		return true;
	return false;
}

void ChuyenBay::setDSVe(DsVeMayBay dsVe) { this->dsVe = dsVe; }

DsVeMayBay ChuyenBay::getDSVe() { return this->dsVe; }

/**
 * @brief Đây là hàm thử nghiệm
 *
 */
void ChuyenBay::ThucHienCB(DsMayBay DsMB)
{

	MayBay *tmp = DsMB.findMB(this->idMayBay);
	tmp->tangSoLuotThucHienCB();
}

Date ChuyenBay::ngayHoanThanh()
{
	Date date;
	if (ngayGio.getGio() + 2 < 24)
	{
		date.setNgay(ngayGio.getNgay());
		date.setThang(ngayGio.getThang());
		date.setNam(ngayGio.getNam());
		date.setGio(ngayGio.getGio() + 2);
		date.setPhut(ngayGio.getPhut());
	}
	else
	{
		date.setNgay(ngayGio.getNgay() + 1);
		date.setThang(ngayGio.getThang());
		date.setNam(ngayGio.getNam());
		date.setGio(ngayGio.getGio() + 2 - 24);
		date.setPhut(ngayGio.getPhut());
	}
	int thang;
	thang = ngayGio.getThang();
	if ((thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 ||
		 thang == 10) &&
		date.getNgay() == 32)
	{
		date.setThang(thang + 1);
		date.setNgay(1);
	}
	if (thang == 12 && date.getNgay() == 32)
	{
		date.setThang(1);
		date.setNgay(1);
		date.setNam(ngayGio.getNam() + 1);
	}
	if ((thang == 4 || thang == 6 || thang == 9 || thang == 11) &&
		date.getNgay() == 31)
	{
		date.setThang(thang + 1);
		date.setNgay(1);
	}
	if (laNamNhuan(ngayGio.getNam()) == 1)
	{
		if (thang == 2 && date.getNgay() == 30)
		{
			date.setThang(3);
			date.setNgay(1);
		}
	}
	else
	{
		if (thang == 2 && date.getNgay() == 29)
		{
			date.setThang(3);
			date.setNgay(1);
		}
	}
	return date;
}

// @return true nếu thời gian của CBay hiện tại cách xa <Date another> <hour> tiếng trở lên
bool ChuyenBay::cach(int hour, Date another)
{
	long long date1 = ngayGio.soVoi1_1_1900_0_0();
	long long date2 = another.soVoi1_1_1900_0_0();
	if (abs(date1 - date2) > hour * 60)
	{
		return true;
	}
	return 0;
}

bool ChuyenBay::operator<(const ChuyenBay &other)
{
	int compare = strcmp(maCB, other.maCB);
	return (compare < 0) ? true : false;
}

ChuyenBay NodeCB::getNode() { return this->chuyenBay; }

NodeCB::NodeCB()
{
	this->chuyenBay = ChuyenBay();
	this->next = NULL;
}

NodeCB::NodeCB(ChuyenBay chuyenBay)
{
	this->chuyenBay = chuyenBay;
	this->next = NULL;
}

void NodeCB::setCb(ChuyenBay chuyenBay) { this->chuyenBay = chuyenBay; }

bool NodeCB::hasNext()
{
	if (this->next == NULL)
		return false;
	return true;
}

void NodeCB::setNext(NodeCB *next) { this->next = next; }

NodeCB *NodeCB::getNext() { return this->next; }

NodeCB *NodeCB::getTail()
{
	NodeCB *tmp = this;
	while (tmp->hasNext())
		tmp = tmp->getNext();
	return tmp;
}

// Hàm của DsChuyenBay

DsChuyenBay::DsChuyenBay()
{
	this->head = NULL;
	size = 0;
}

DsChuyenBay::DsChuyenBay(NodeCB *cb) { this->head = cb; }

void DsChuyenBay::push(NodeCB *currNode, NodeCB *node)
{
	node->setNext(currNode->getNext());
	currNode->setNext(node);
}

void DsChuyenBay::pushBack(NodeCB *node)
{
	NodeCB *tmp = this->head;
	tmp = tmp->getTail();
	push(tmp, node);
}

void DsChuyenBay::pushFront(NodeCB *node)
{
	if (this->head == NULL)
	{
		setHead(node);
	}
	else
	{
		node->setNext(this->head);
		this->head = node;
	}
}

void DsChuyenBay::insertOrder(NodeCB *node)
{
	NodeCB *tmp = head;

	if (strcmp(head->getNode().getMaCB(), node->getNode().getMaCB()) > 0)
	{
		pushFront(node);
		return;
	}

	while (tmp != NULL)
	{
		if (!tmp->hasNext() || strcmp(tmp->getNext()->getNode().getMaCB(),
									  node->getNode().getMaCB()) > 0)
			break;
		tmp = tmp->getNext();
	}
	if (tmp != NULL)
		push(tmp, node);
	else
		pushBack(node);
}

void DsChuyenBay::setHead(NodeCB *head) { this->head = head; }

NodeCB *DsChuyenBay::getHead() { return head; }

void DsChuyenBay::setSize()
{
	NodeCB *tmp = this->head;
	size = 0;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->getNext();
	}
}

int DsChuyenBay::getSize() { return size; }

void DsChuyenBay::pop(NodeCB *node)
{
	if (node == this->head)
	{
		popFirst();
		return;
	}
	else if (!node->hasNext())
	{
		popBack();
		return;
	}

	NodeCB *tmp = this->head;
	while (tmp->getNext() != node)
	{
		tmp = tmp->getNext();
	}
	tmp->setNext(node->getNext());
	delete node;
	node = 0;
}

void DsChuyenBay::popFirst()
{
	if (this->head != NULL)
	{
		this->head = this->head->getNext();
		size--;
	}
}

void DsChuyenBay::popBack()
{
	if (this->head == NULL)
		return;
	NodeCB *tmp = this->head;
	while (tmp->getNext()->hasNext())
	{
		tmp = tmp->getNext();
	}
	tmp->setNext(nullptr);
	size--;
}

NodeCB *DsChuyenBay::timCB(const char *maCB)
{
	NodeCB *tmp = this->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->getNode().getMaCB(), maCB) == 0)
		{
			return tmp;
		}
		tmp = tmp->getNext();
	}

	return nullptr;
}

bool DsChuyenBay::isAval(const char *soHieuMB, Date timeCB, const char *_maCB)
{
	NodeCB *tmp = this->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->getNode().getMaCB(), _maCB) == 0)
		{
			tmp = tmp->getNext();
			continue;
		}

		if (tmp->getNode().getTrangThai() == HuyChuyen)
		{
			tmp = tmp->getNext();
			continue;
		}
		if (!tmp->getNode().cach(3, timeCB))
		{
			if (strcmp(tmp->getNode().getMaMayBay(), soHieuMB) == 0)
				return false;
		}

		tmp = tmp->getNext();
	}

	return true;
}

bool DsChuyenBay::isExist(const char *maCB)
{
	NodeCB *tmp = this->head;
	while (tmp != NULL)
	{

		if (strcmp(tmp->getNode().getMaCB(), maCB) == 0)
			return true;

		tmp = tmp->getNext();
	}

	return false;
}

bool DsChuyenBay::isUsing(const char *maMB)
{
	NodeCB *tmp = this->head;
	Date now;

	while (tmp != NULL)
	{
		now.setToNow();
		if ((tmp->getNode().getTrangThai() == ConVe || tmp->getNode().getTrangThai() == HetVe) && (tmp->getNode().ngayHoanThanh() < now))
		{
			if (strcmp(tmp->getNode().getMaMayBay(), maMB) == 0)
				return true;
		}

		tmp = tmp->getNext();
	}

	return false;
}

int DsChuyenBay::duocDatKhong(string cmnd, ChuyenBay cb)
{
	NodeCB *tmp = this->head;
	for (int i = 0; i < cb.getDSVe().getSoVeToiDa(); i++)
	{
		if (cb.getDSVe().getVe(i).getHanhKhach() == cmnd)
			return 1;
	}

	while (tmp != NULL)
	{
		if (tmp->getNode().getMaCB() == cb.getMaCB())
		{
			tmp = tmp->getNext();
			continue;
		}

		if ((tmp->getNode().getTrangThai() == ConVe ||
			 tmp->getNode().getTrangThai() == HetVe) &&
			!tmp->getNode().cach(6, cb.getNgayGio()))
		{
			for (int i = 0; i < tmp->getNode().getDSVe().getSoVeToiDa(); i++)
			{

				if (tmp->getNode().getDSVe().getVe(i).getHanhKhach() == cmnd)
					return 2;
			}
		}

		tmp = tmp->getNext();
	}

	return 0;
}

void DsChuyenBay::readFromFile(DsMayBay &listMB)
{
	bool gotBug = false;
	ifstream file(dataCBPath[pathBugLv], ios::in);
	if (file.is_open())
	{
		this->head = nullptr;
		string maCB, noiDen, trangThai, idMayBay, ngay, thang, nam, gio, phut,
			soVeMax, soVeAval;
		string line = "";

		while (getline(file, line))
		{
			bool isGood = true;
			stringstream s(line);

			getline(s, maCB, '|');
			getline(s, idMayBay, '|');

			getline(s, ngay, '|');
			getline(s, thang, '|');
			getline(s, nam, '|');
			getline(s, gio, '|');
			getline(s, phut, '|');
			Date d = Date(stoi(ngay), stoi(thang), stoi(nam), stoi(gio), stoi(phut));

			getline(s, noiDen, '|');
			ChuyenBay cb = ChuyenBay(maCB.c_str(), noiDen, d, idMayBay.c_str());
			getline(s, trangThai, '|');
			cb.setTrangThai(stoi(trangThai));

			getline(s, soVeMax, '|');
			getline(s, soVeAval, '|');
			DsVeMayBay dsVe = cb.getDSVe();
			dsVe.setSoVeToiDa(stoi(soVeMax));
			dsVe.setSoVeDaDat(stoi(soVeMax) - stoi(soVeAval));
			cout << dsVe.getSoVeDaDat() << endl;
			MayBay *mbData = listMB.findMB(cb.getMaMayBay());
			if (mbData == NULL)
			{
				isGood = false;
			}
			else
				dsVe.setDSVe(mbData);

			if (!mbData->inUsed())
			{
				mbData->setUsed();
				gotBug = true;
			}

			for (int i = 0; i < dsVe.getSoVeDaDat(); i++)
			{
				string pos = "", cmnd = "";

				getline(s, pos, '|');
				if (pos == "")
					break;
				getline(s, cmnd, '|');
				VeMayBay t_ve = dsVe.getVe(stoi(pos));
				t_ve.setHanhKhach(cmnd);

				dsVe.setVe(t_ve, stoi(pos));
			}
			cout << maCB << "===========" << endl;
			for (int i = 0; i < dsVe.getSoVeToiDa(); i++)
			{
				if (dsVe.getVe(i).getHanhKhach() != "")
					cout << dsVe.getVe(i).getIDVe() << dsVe.getVe(i).getHanhKhach() << endl;
			}
			cb.setDSVe(dsVe);

			NodeCB *node = new NodeCB();
			node->setCb(cb);
			if (isGood)
				if (head == NULL)
				{
					setHead(node);
				}
				else
					insertOrder(node);
		}
		setSize();

		if (gotBug)
		{
			listMB.writetoFile();
		}
		cout << "Nhập file chuyến bay===========================" << endl;
	}
	else
		cout << "Error" << endl;
	file.close();
}
void DsChuyenBay::writetToFile()
{
	ofstream file(dataCBPath[pathBugLv], ios::out | ios::trunc);
	if (file.is_open())
	{
		NodeCB *tmp = this->head;
		while (tmp != NULL) //
		{
			file << tmp->getNode().getMaCB() << "|"
				 << tmp->getNode().getMaMayBay() << "|"
				 << tmp->getNode().getNgayGio().getNgay() << "|"
				 << tmp->getNode().getNgayGio().getThang() << "|"
				 << tmp->getNode().getNgayGio().getNam() << "|"
				 << tmp->getNode().getNgayGio().getGio() << "|"
				 << tmp->getNode().getNgayGio().getPhut() << "|"
				 << tmp->getNode().getNoiDen() << "|"
				 << tmp->getNode().getTrangThai() << "|";

			file << tmp->getNode().getDSVe().getSoVeToiDa() << "|" << tmp->getNode().getDSVe().getSoVeConLai() << "|";

			for (int i = 0; i < tmp->getNode().getDSVe().getSoVeToiDa(); i++)
			{
				if (tmp->getNode().getDSVe().getVe(i).getHanhKhach() != "")
				{
					file << i << "|" << tmp->getNode().getDSVe().getVe(i).getHanhKhach() << "|";
				}
			}
			file << endl;

			tmp = tmp->getNext();
		}
		cout << "Xuất file chuyến bay========================" << endl;
	}
	else
	{
		cout << "Error";
	}
	file.close();
}

bool DsChuyenBay::update(DsMayBay DsMB)
{
	Date now;
	now.setToNow();

	bool changed = false;

	NodeCB *tmp = this->head;

	while (tmp != NULL)
	{
		if (tmp->getNode().getTrangThai() == 1 ||
			tmp->getNode().getTrangThai() == 2)
		{
			if (tmp->getNode().ngayHoanThanh() < now)
			{
				ChuyenBay cb_t = tmp->getNode();
				cb_t.setTrangThai(HoanTat);
				cb_t.ThucHienCB(DsMB);
				tmp->setCb(cb_t);
				// tmp->getNode().ThucHienCB();
				changed = true;
			}
		}

		if (tmp->getNode().getTrangThai() == 1 &&
			tmp->getNode().getDSVe().getSoVeConLai() == 0)
		{
			ChuyenBay cb_t = tmp->getNode();
			cb_t.setTrangThai(HetVe);
			tmp->setCb(cb_t);
			changed = true;
		}

		tmp = tmp->getNext();
	}

	if (changed)
	{
		writetToFile();

		return true;
	}

	return false;
}

void DsChuyenBay::deleteDs()
{
	NodeCB *tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->getNext();
		tmp->getNode().getDSVe().deleteDsVe();
		delete tmp;
		tmp = 0;
	}
}
void getDataFromFile(DsChuyenBay &listCB, DsMayBay &listMB, DsHanhKhach &listHK)
{
	listMB.readFromFile();
	listCB.readFromFile(listMB);
	listHK.readFromFile();

	cout << "Nhận lại toàn bộ dữ liệu từ file!" << endl;
}

void setDataToFile(DsChuyenBay &listCB, DsMayBay &listMB, DsHanhKhach &listHK)
{
	listMB.writetoFile();
	listHK.writeToFileAllHK();
	listCB.writetToFile();

	cout << "Xuất toàn bộ dữ liệu vào file!" << endl;
}
