#include "SVGViewer.h"
#include <QFileDialog>
#include <QColorDialog>

SVGViewer::SVGViewer(QWidget *parent)
    : QMainWindow(parent), m_pixmap(QSize(16, 16))
{
    ui.setupUi(this);
    m_pixmap.fill(m_color);
    ui.selectColor->setIcon(QIcon(m_pixmap));
}

void SVGViewer::on_actionOpenFile_triggered(bool val)
{
    auto _filePath = QFileDialog::getOpenFileName(this, QStringLiteral("打开SVG文件"), "", "SVG (*.svg)");
    if (!_filePath.isEmpty())
    {
        ui.graphicsView->openFile(_filePath);
        setOption();
    }
}

void SVGViewer::on_actionOpenFolder_triggered(bool val)
{
    QFileDialog _dialog(this, QStringLiteral("打开目录"));
    _dialog.setFileMode(QFileDialog::Directory);
    if (_dialog.exec())
    {
        auto _folderPath = _dialog.selectedFiles().value(0);
        if (!_folderPath.isEmpty())
        {
            auto _model = new SvgIconFileSystemModel();
            ui.treeView->setModel(_model);
            ui.treeView->setHeaderHidden(true);
            ui.treeView->header()->hideSection(1);
            ui.treeView->header()->hideSection(2);
            ui.treeView->header()->hideSection(3);
            ui.treeView->setRootIndex(_model->setRootPath(_folderPath));

            connect(ui.treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
                    [&](const QItemSelection &selected, const QItemSelection &deselected) {
                if (selected.indexes().count())
                {
                    auto _model = static_cast<SvgIconFileSystemModel *>(ui.treeView->model());
                    auto _filePath = _model->filePath(selected.indexes().first());
                    if (!_filePath.isEmpty())
                    {
                        ui.graphicsView->openFile(_filePath);
                        setOption();
                    }
                }
            });
        }
    }
}

void SVGViewer::on_actionExit_triggered(bool val)
{
    qApp->quit();
}

void SVGViewer::on_highQualityAntialiasing_clicked()
{
    setOption();
}

void SVGViewer::on_viewBackground_clicked()
{
    setOption();
}

void SVGViewer::on_viewOutline_clicked()
{
    setOption();
}

void SVGViewer::on_colorize_clicked()
{
    setOption();
}

void SVGViewer::on_selectColor_clicked()
{
    auto _color = QColorDialog::getColor(m_color, this);
    if (_color.isValid())
    {
        m_color = _color;
        m_pixmap.fill(m_color);
        ui.selectColor->setIcon(QIcon(m_pixmap));
        ui.graphicsView->setColor(m_color);
    }
}

void SVGViewer::setOption()
{
    ui.graphicsView->setHighQualityAntialiasing(ui.highQualityAntialiasing->isChecked());
    ui.graphicsView->setViewBackground(ui.viewBackground->isChecked());
    ui.graphicsView->setViewOutline(ui.viewOutline->isChecked());
    ui.graphicsView->setColorize(ui.colorize->isChecked());
    ui.graphicsView->setColor(m_color);
}