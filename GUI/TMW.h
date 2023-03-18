#pragma once
#include <QAbstractTableModel>
#include "/Users/robi_/source/repos/Tema 6-7 OOP/Tema 6-7 OOP/Domain.h"
#include <vector>
#include <qdebug.h>
#include <qbrush.h>
#include <qfont.h>

class MyTableModel :public QAbstractTableModel {
	std::vector<Carte> carti;
public:
	MyTableModel(const std::vector<Carte>& carti) :carti{ carti } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return carti.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 3;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::ForegroundRole) {
			Carte c = carti[index.row()];
			if (c.getAn() > 2022) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::FontRole) {
			Carte c = carti[index.row()];
			if (c.getGen() == "basm") {
				QFont f;
				f.setBold(1);
				f.setItalic(1);
				f.setUnderline(1);
				return f;
			}
		}
		if (role == Qt::DisplayRole) {

			Carte c = carti[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(c.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(c.getAutor());
			}
			else if (index.column() == 2) {
				return QString::number(c.getAn());
			}
		}
		if (role == Qt::UserRole) {
			return QString::fromStdString(carti[index.row()].getTitlu());
		}
		return QVariant{};
	}

	void setCarti(const std::vector<Carte>& carti) {
		if (rowCount() > carti.size())
			this->removeRows(carti.size(), rowCount() - carti.size());
		else if (rowCount() < carti.size()) {
			this->insertRows(rowCount(), carti.size() - rowCount());
		}
		
		this->carti = carti;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	bool insertRows (int row, int count, const QModelIndex &parent = QModelIndex()) override {
		beginInsertRows(parent, row, row + count -1);
		endInsertRows();
		return  true;
	}

	bool removeRows (int row, int count, const QModelIndex& parent = QModelIndex()) override {
		beginRemoveRows(parent, row, row + count - 1);
		endRemoveRows();
		return true;
	}
};