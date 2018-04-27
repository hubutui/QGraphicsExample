#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{
    // Open an image file, get its name, and store in imagePath
    QString imagePath = QFileDialog::getOpenFileName(
                this,
                tr("Open Image"),
                QDir::currentPath(),
                tr("*"));

    if (imagePath.isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("Not a valid image"));
        return;
    }

    // create a QImage object
    QImage image(imagePath);

    // create a QPixmap object from QImage
    QPixmap pixmap = QPixmap::fromImage(image);

    // create scene
    QGraphicsScene *scene = new QGraphicsScene;

    // add image to scene
    scene->addPixmap(pixmap);
    // set visible rectangle
    scene->setSceneRect(pixmap.rect());
    // important attach QGraphicsView with QGraphicsScene
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_action_Quit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionDraw_Sine_Chart_triggered()
{
    QSplineSeries *spline = new QSplineSeries;

    for (double x = -M_PI; x < M_PI; x += 0.01) {
        spline->append(x, sin(x));
    }

    spline->setName(tr("Sine Curve"));
    spline->setUseOpenGL(true);

    QChart *chart = new QChart;

    chart->addSeries(spline);
    chart->createDefaultAxes();
    chart->axisX()->setRange(-4, 4);
    chart->axisY()->setRange(-1.2, 1.2);
    chart->setTheme(QChart::ChartThemeBlueIcy);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setGeometry(ui->graphicsView->rect());

    // important
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addItem(chart);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setScene(scene);
}
