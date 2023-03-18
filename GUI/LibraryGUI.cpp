#include "LibraryGUI.h"
#include <qformlayout.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qlist.h>
#include <qlistview.h>
#include <qlistwidget.h>
#include <string>
#include <fstream>

void LibraryGUI::initGUICmps() {
	setLayout(Layout);
	
	
	QWidget* widRght = new QWidget;
	QFormLayout* formRght = new QFormLayout;
	widRght->setLayout(formRght);

	//lst = new QListWidget;
	formRght->addRow(lst);
		
	//t = new QTableWidget;
	//formRght->addItem(this->t);

	QWidget* wid3 = new QWidget;
	QGridLayout* grid = new QGridLayout;
	wid3->setLayout(grid);

	grid->addWidget(btnSort1, 0, 0);
	grid->addWidget(btnSort2, 0, 1);
	grid->addWidget(btnSort3, 0, 2);


	grid->addWidget(filter1, 5, 0);
	grid->addWidget(flt1, 4, 1, 3, 2);
	grid->addWidget(filter2, 7, 0);
	grid->addWidget(flt2, 5, 1, 5, 2);

	grid->addWidget(undo, 9, 0);
	grid->addWidget(reload, 9, 2);


	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);

	QLabel* x = new QLabel("Titlu carte:");
	formLDetalii->addRow(x, txtTitlu);

	QLabel* y = new QLabel("Autor carte:");
	formLDetalii->addRow(y, txtAutor);
	

	QLabel* z = new QLabel("Gen carte:");
	formLDetalii->addRow(z, txtGen);

	QLabel* t = new QLabel("An aparitie carte:");
	formLDetalii->addRow(t, txtAn);

	QWidget* widMod = new QWidget;
	QHBoxLayout* formMod = new QHBoxLayout;

	widMod->setLayout(formMod);
	formMod->addWidget(btnAdd);
	formMod->addWidget(btnMod);
	formMod->addWidget(btnRemove);

	formLDetalii->addItem(new QSpacerItem(0, 100, QSizePolicy::Expanding, QSizePolicy::Expanding));

	QHBoxLayout* formCos = new QHBoxLayout;
	formCos->addWidget(Basket);
	formCos->addWidget(btnBskt);

	formLDetalii->addRow(widMod);

	formLDetalii->addItem(new QSpacerItem(0, 100, QSizePolicy::Expanding, QSizePolicy::Expanding));

	formLDetalii->addRow(formCos);
	Layout->addWidget(widDetalii);
	Layout->addWidget(widRght);
	Layout->addWidget(wid3);
	//MyListModel* m = new MyListModel(ctr.getCarti());
	//tbl->setModel(m);
	m = new MyTableModel(ctr.getCarti());
	tbl->setModel(m);
	Layout->addWidget(tbl);
}


void LibraryGUI::loadTable(const std::vector<Carte> v) {
	
	/*tbl->clear();
	tbl->setRowCount(v.size());
	tbl->setColumnCount(1);
	for (int i = 0; i < v.size(); i++) {
		tbl->setItem(i, 0, new QTableWidgetItem(v[i].getTitlu().c_str()));
	}*/
	m->setCarti(v);
}

void LibraryGUI::reloadList(vector<Carte> v) {
	lst->clear();
	int i=0;
	for (auto carte : v) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(carte.getTitlu()));
		item->setData(Qt::UserRole, QString::fromStdString(std::to_string(i)));
		item->setBackground(Qt::red);
		lst->addItem(item);
		i++;
	}
}

/*void LibraryGUI::reloadList(vector<Carte> v) {
	t->clear();
	int i = 0;
	for (auto carte : v) {
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(carte.getTitlu()));
		t->addItem(item);
		i++;
	}
}*/

void LibraryGUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &LibraryGUI::GUI_Add);
	QObject::connect(btnRemove, &QPushButton::clicked, this, &LibraryGUI::GUI_Del);
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		//reloadList(ctr.getCarti());
		auto selected = lst->selectedItems();
		if (selected.isEmpty()) {
			idd = -1;
			txtAn->setText("");
			txtAutor->setText("");
			txtGen->setText("");
			txtTitlu->setText("");
		}
		else {
			auto item = selected.at(0);
			item->setBackground(Qt::green);
			QString idq = item->data(Qt::UserRole).toString();
			string id = idq.toStdString();
			idd = std::stoi(id);
			auto c = ctr.getCarti()[idd];
			txtAn->setText(QString::fromStdString(std::to_string(c.getAn())));
			txtAutor->setText(QString::fromStdString(c.getAutor()));
			txtGen->setText(QString::fromStdString(c.getGen()));
			txtTitlu->setText(QString::fromStdString(c.getTitlu()));
		}
		});
	QObject::connect(btnMod, &QPushButton::clicked, this, &LibraryGUI::GUI_Mod);
	QObject::connect(undo, &QPushButton::clicked, this, &LibraryGUI::GUI_Undo);
	QObject::connect(btnSort1, &QPushButton::clicked, this, &LibraryGUI::GUI_Sort1);
	QObject::connect(btnSort2, &QPushButton::clicked, this, &LibraryGUI::GUI_Sort2);
	QObject::connect(btnSort3, &QPushButton::clicked, this, &LibraryGUI::GUI_Sort3);
	QObject::connect(filter1, &QPushButton::clicked, this, &LibraryGUI::GUI_Filter1);
	QObject::connect(filter2, &QPushButton::clicked, this, &LibraryGUI::GUI_Filter2);
	QObject::connect(reload, &QPushButton::clicked, this, &LibraryGUI::GUI_reload);
	QObject::connect(Basket, &QPushButton::clicked, this, &LibraryGUI::GUI_Basket);
	QObject::connect(btnBskt, &QPushButton::clicked, this, &LibraryGUI::GUI_Basket_show);
}

void LibraryGUI::GUI_Add() {
	try {
		ctr.adauga(txtTitlu->text().toStdString(), txtAutor->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt());
		reloadList(ctr.getCarti());
		loadTable(ctr.getCarti());
	}
	catch (ExceptiiValidator& ev) {
		std::string s = ev.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	catch (RepoException& re) {
		std::string s = re.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	catch (std::exception& s) {
		QMessageBox::warning(this, "Warning", "Book already added");
	}
}

void LibraryGUI::GUI_Del() {
	try {
		string t = txtTitlu->text().toStdString();
		string a = txtAutor->text().toStdString();
		if (t != "" && a != "") {
			try {
				ctr.sterge(ctr.find(t, a));
				reloadList(ctr.getCarti());
				loadTable(ctr.getCarti());
			}
			catch (ExceptiiValidator& ev) {
				std::string s = ev.getError();
				QMessageBox::warning(this, "Warning", QString::fromStdString(s));
			}
			catch (RepoException& re) {
				std::string s = re.getError();
				QMessageBox::warning(this, "Warning", QString::fromStdString(s));
			}
		}
	}
	catch (std::exception) {
		QMessageBox::warning(this, "Warning", "Invalid arguments");
	}
}

void LibraryGUI::GUI_Mod() {
	if (idd >= 0)
	{
		try {
			ctr.modifica(idd, txtTitlu->text().toStdString(), txtAutor->text().toStdString(), txtGen->text().toStdString(), txtAn->text().toInt());
			reloadList(ctr.getCarti());
			loadTable(ctr.getCarti());
		}

		catch (ExceptiiValidator& ev) {
			std::string s = ev.getError();
			QMessageBox::warning(this, "Warning", QString::fromStdString(s));
		}
		catch (RepoException& re) {
			std::string s = re.getError();
			QMessageBox::warning(this, "Warning", QString::fromStdString(s));
		}
	}
	else QMessageBox::warning(this, "Warning", "Please select a book first");
}

void LibraryGUI::GUI_Undo() {
	try {
		ctr.undo();
		reloadList(ctr.getCarti());
		loadTable(ctr.getCarti());
	}
	catch (std::exception) {
		QMessageBox::warning(this, "Warning", "Can't execute Undo operation");
	}
}

void LibraryGUI::GUI_Sort1() {
	ctr.t_sort();
	reloadList(ctr.getCarti());
	loadTable(ctr.getCarti());
}

void LibraryGUI::GUI_Sort2() {
	ctr.a_sort();
	reloadList(ctr.getCarti());
	loadTable(ctr.getCarti());
}

void LibraryGUI::GUI_Sort3() {
	ctr.an_sort();
	reloadList(ctr.getCarti());
	loadTable(ctr.getCarti());
}

void LibraryGUI::GUI_Filter1() {
	aux.clear();
	try {
		this->ctr.t_filtrare(aux, flt1->text().toStdString());
		reloadList(aux);
		loadTable(aux);
	}
	catch (ExceptiiValidator& ev) {
		std::string s = ev.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	catch (RepoException& re) {
		std::string s = re.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
}

void LibraryGUI::GUI_Filter2() {
	aux.clear();
	try {
		aux = this->ctr.a_filtrare(std::stoi(flt2->text().toStdString()));
		reloadList(aux);
		loadTable(aux);
	}
	catch (ExceptiiValidator& ev) {
		std::string s = ev.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	catch (RepoException& re) {
		std::string s = re.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	catch (std::exception) {
		QMessageBox::warning(this, "Warning", "Empty input");
	}
}

void LibraryGUI::GUI_reload() {
	reloadList(ctr.getCarti());
	loadTable(ctr.getCarti());
}

void LibraryGUI::GUI_Basket() {
	 BasketGUI* q = new BasketGUI(ctr);
	 BGUI* b = new BGUI(*q);
	 q->show();
	 b->show();
	 this->btnBskt->hide();
	 this->Basket->hide();
}

void LibraryGUI::GUI_Basket_show() {
	BasketGUI* q = new BasketGUI(ctr);
	q->show();
}

void BasketGUI::initGUICmps() {
	/*
	setLayout(layout);

	QWidget* widLft = new QWidget;
	QFormLayout* frmLft = new QFormLayout;
	widLft->setLayout(frmLft);

	QLabel* x = new QLabel("Titlu carte:");
	frmLft->addRow(x, txtTitlu);

	QLabel* y = new QLabel("Autor carte:");
	frmLft->addRow(y, txtAutor);


	QLabel* z = new QLabel("Gen carte:");
	frmLft->addRow(z, txtGen);

	QLabel* t = new QLabel("An aparitie carte:");
	frmLft->addRow(t, txtAn);

	layout->addWidget(widLft);
	*/
	setLayout(layout);


	QWidget* widRght = new QWidget;
	QFormLayout* formRght = new QFormLayout;
	widRght->setLayout(formRght);

	list = new QListWidget;
	formRght->addRow(list);


	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);

	QLabel* x = new QLabel("Titlu carte:");
	formLDetalii->addRow(x, txtTitlu);

	QLabel* y = new QLabel("Autor carte:");
	formLDetalii->addRow(y, txtAutor);

	QWidget* widMod = new QWidget;
	QHBoxLayout* formMod = new QHBoxLayout;

	widMod->setLayout(formMod);
	formMod->addWidget(btnAdd);
	formMod->addWidget(btnEmpty);

	//formLDetalii->addItem(new QSpacerItem(0, 50, QSizePolicy::Expanding, QSizePolicy::Expanding));

	QWidget* rnd = new QWidget;
	QHBoxLayout* frnd = new QHBoxLayout;
	rnd->setLayout(frnd);

	frnd->addWidget(btnRndAdd);
	frnd->addWidget(random);

	formLDetalii->addItem(new QSpacerItem(0, 50, QSizePolicy::Expanding, QSizePolicy::Expanding));
	formLDetalii->addRow(widMod);
	formLDetalii->addItem(new QSpacerItem(0, 100, QSizePolicy::Expanding, QSizePolicy::Expanding));
	formLDetalii->addRow(rnd);

	QWidget* widMod2 = new QWidget;
	QHBoxLayout* formMod2 = new QHBoxLayout;

	widMod2->setLayout(formMod2);
	formMod2->addWidget(btnExport);


	formLDetalii->addItem(new QSpacerItem(0, 50, QSizePolicy::Expanding, QSizePolicy::Expanding));
	formLDetalii->addRow(widMod2);

	QWidget* wid3 = new QWidget;
	QFormLayout* form3 = new QFormLayout;
	wid3->setLayout(form3);
	
	QLabel* txtR = new QLabel("Rapoarte^");
	form3->addRow(l);
	form3->addRow(txtR);

	layout->addWidget(widDetalii);
	layout->addWidget(widRght);
	layout->addWidget(wid3);
}

void BasketGUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &BasketGUI::GUI_Add);
	QObject::connect(btnEmpty, &QPushButton::clicked, this, &BasketGUI::GUI_Empty);
	QObject::connect(btnExport, &QPushButton::clicked, this, &BasketGUI::GUI_Export);
	QObject::connect(btnRndAdd, &QPushButton::clicked, this, &BasketGUI::GUI_rndAdd);
}

void BasketGUI::GUI_Add() {
	try {
		basket->adauga_cos(ctr.find(txtTitlu->text().toStdString(),txtAutor->text().toStdString()));
		reloadList();
		notify();
	}
	catch (ExceptiiValidator& ev) {
		std::string s = ev.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
	catch (RepoException& re) {
		std::string s = re.getError();
		QMessageBox::warning(this, "Warning", QString::fromStdString(s));
	}
}

void BasketGUI::GUI_Empty() {
	basket->goleste_cos();
	reloadList();
	notify();
}

void BasketGUI::GUI_rndAdd() {
	if (ctr.getCarti().size() == 0) {
		QMessageBox::warning(this, "Warning", "No books available");
	}
	else
	{
		try {
			int n = std::stoi(random->text().toStdString());
			while (n) {
				std::mt19937 mt{ std::random_device{}() };
				std::uniform_int_distribution<> dist(0, ctr.getCarti().size() - 1);
				int rndNr = dist(mt);
				n--;
				basket->adauga_cos(ctr.getCarti()[rndNr]);
				reloadList();
			}
		}
		catch (std::exception) {
			QMessageBox::warning(this, "Warning", "Insert a number");
		}
		notify();
	}
}

void BasketGUI::GUI_Export() {
	std::ofstream fout("Test.txt");
	for (const auto& carte : basket->get_all()) {
		fout << "'" << carte.getTitlu() << "' - " << carte.getAutor() << " | " << carte.getGen() << " -> " << carte.getAn() << "\n";
	}
	return;
}

void BasketGUI::GUI_Reports() {
	Raport raport = basket->get_raport();
	for (const auto& carte : ctr.getCarti()) {
		Elem e(carte.getGen());
		raport.add(carte.getGen(), e);
	}
	l->clear();
	for (auto rap : raport.get_r()) {
		for (const auto& carte : basket->get_all())
			if (carte.getGen() == rap.first)
				rap.second.increase();
		
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString((rap.first)+std::to_string(rap.second.get_count())));
		l->addItem(item);
	}

}

void BasketGUI::reloadList() {
	list->clear();
	int i = 0;
	for (auto carte : basket->get_all()) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(carte.getTitlu()));
		item->setData(Qt::UserRole, QString::fromStdString(std::to_string(i)));
		list->addItem(item);
		i++;
	}
	GUI_Reports();
}