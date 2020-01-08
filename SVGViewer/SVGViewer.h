#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SVGViewer.h"

class SVGViewer : public QMainWindow
{
    Q_OBJECT

public:
    SVGViewer(QWidget *parent = Q_NULLPTR);
private slots:
    void on_actionOpenFile_triggered(bool val);
    void on_actionOpenFolder_triggered(bool val);
    void on_actionExit_triggered(bool val);
    void on_highQualityAntialiasing_clicked();
    void on_viewBackground_clicked();
    void on_viewOutline_clicked();
    void on_colorize_clicked();
    void on_selectColor_clicked();
private:
    void setOption();
private:
    Ui::SVGViewerClass ui;
    QColor m_color = QColor(Qt::black);
    QPixmap m_pixmap;
};

#include <QFileSystemModel>
class SvgIconFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
    SvgIconFileSystemModel(QObject *parent = nullptr) : QFileSystemModel(parent) {}
public:
    QVariant data(const QModelIndex &index, int role) const override
    {
        if (role == Qt::DecorationRole)
        {
            QFileInfo info = fileInfo(index);

            if (info.isFile() && info.suffix().compare("svg", Qt::CaseInsensitive) == 0)
            {
                return QIcon(info.filePath());
            }
        }
        return QFileSystemModel::data(index, role);
    }
};