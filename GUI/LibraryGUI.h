#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include <vector>
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Service.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Repo.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Domain.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Cos.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Export.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Elem.h"
#include "C:\Users\robi_\source\repos\Tema 6-7 OOP\Tema 6-7 OOP\Raport.h"
#include <qlabel.h>
#include <qmessagebox.h>
#include "Observer.h"
#include <qpainter.h>
#include <minmax.h>
#include <qtablewidget.h>
#include "TMW.h"


class BasketGUI : public QWidget, public Observable{
private:
	Service& ctr;
	Cos* basket = new Cos;
	QHBoxLayout* layout = new QHBoxLayout;
	QListWidget* list = new QListWidget;
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtAutor = new QLineEdit;
	QLineEdit* random = new QLineEdit;
	QPushButton* btnAdd = new QPushButton("Add");
	QPushButton* btnEmpty = new QPushButton("Empty basket");
	QPushButton* btnRndAdd = new QPushButton("Random add");
	QPushButton* btnExport = new QPushButton("Export");
	QListWidget* l = new QListWidget();
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList();
public:
	BasketGUI(Service& ctr) : ctr{ ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList();
	}
	void GUI_Add();
	void GUI_Empty();
	void GUI_rndAdd();
	void GUI_Export();
	void GUI_Reports();
	const vector<Carte>& lista() const {
		return basket->get_all();
	}
};

class LibraryGUI : public QWidget{
private:
	Service& ctr;
	QHBoxLayout* Layout = new QHBoxLayout;
	QListWidget* lst = new QListWidget;
	QTableView* tbl = new QTableView;
	MyTableModel* m;
	QPushButton* btnSort1 = new QPushButton("Sort by title");
	QPushButton* btnSort2 = new QPushButton("Sort by author");
	QPushButton* btnSort3 = new QPushButton("Sort by year");
	QPushButton* undo = new QPushButton("Undo");
	QPushButton* filter1 = new QPushButton("Title filter");
	QLineEdit* flt1 = new QLineEdit;
	QPushButton* filter2 = new QPushButton("Year filter");
	QLineEdit* flt2 = new QLineEdit;
	QPushButton* reload = new QPushButton("Reload");
	QPushButton* Basket = new QPushButton("Basket");
	int idd = -1;
	vector<Carte> aux;
	QPushButton* btnAdd = new QPushButton("Add");
	QPushButton* btnMod = new QPushButton("Modify");
	QPushButton* btnRemove = new QPushButton("Remove");
	QPushButton* btnBskt = new QPushButton("Basket(show only)");
	QLineEdit* txtTitlu = new QLineEdit;
	QLineEdit* txtAutor = new QLineEdit;
	QLineEdit* txtGen = new QLineEdit;
	QLineEdit* txtAn = new QLineEdit;
	QVBoxLayout* lyt = new QVBoxLayout;
	QWidget* btn = new QWidget;


	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(vector<Carte> v);
	void loadTable(vector<Carte> v);
public:
	void GUI_Add();
	void GUI_Del();
	void GUI_Mod();
	void GUI_Undo();
	void GUI_Sort1();
	void GUI_Sort2();
	void GUI_Sort3();
	void GUI_Filter1();
	void GUI_Filter2();
	void GUI_reload();
	void GUI_Basket();
	void GUI_Basket_show();
	LibraryGUI(Service& ctr) : ctr{ ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.getCarti());
		loadTable(ctr.getCarti());
	}
};

class BGUI : public QWidget, public Observer {
private:
	BasketGUI& bskt;
public:
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		//QMessageBox::warning(this, "Warning", QString::fromStdString(std::to_string(bskt.lista().size())));
		int c = 20;
		int d = 20;
		for (auto e : this->bskt.lista()) {
			std::mt19937 mt1{ std::random_device{}() };
			std::uniform_int_distribution<> dist1(0, 2);
			int x = dist1(mt1);
			//int x = rand() % 3;
			std::mt19937 mt2{ std::random_device{}() };
			std::uniform_int_distribution<> dist2(10, 100);
			int a = dist2(mt2);
			//srand(time(NULL));
			//int a = rand() % 10;
			std::mt19937 mt3{ std::random_device{}() };
			std::uniform_int_distribution<> dist3(10, 100);
			int b = dist3(mt3);
			//srand(time(NULL));
			//int b = rand() % 10;
			//QMessageBox::information(this, "toPaint", QString::fromStdString(std::to_string(x)));
			if (x == 0) {
				p.drawEllipse(c, d, a, b);
				c += max(a,b);
				if (c + 20 > width()) {
					c = 0;
					d +=max(a,b);
				}
			}
			if (x == 1) {
				p.drawRect(c, d, a, b);
				c += max(a,b);
				if (c + 20 > width()) {
					c = 0;
					d +=max(a,b);
				}
			}
			if (x == 2) {
				p.drawLine(c, d, a, b);
				c += max(a,b);
				if (c + 20 > width()) {
					c = 0;
					d +=max(a,b);
				}
			}
		}
	}

	BGUI(BasketGUI& bskt) : bskt{ bskt } {  bskt.addObserver(this); };

	void update() {
		this->repaint();
	}
};