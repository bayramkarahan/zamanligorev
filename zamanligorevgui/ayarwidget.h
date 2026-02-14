#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QToolButton>
#include <QDialog>
#include <QJsonArray>
#include <functional>

class DatabaseHelper;

class AyarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AyarWidget(const QString& localDir, int boy, QWidget *parent = nullptr);

private:
    void setupUI();
    void fillTable();

    int boy;
    QString localDir;
    QTableWidget *twlh;
    QToolButton *insertTaskButton;
    QToolButton *insertPowerOffButton;
    QToolButton *insertRebootButton;
    QToolButton *insertLogoutButton;
    QToolButton *insertLockButton;
    QToolButton *insertNologinButton;
    DatabaseHelper *db;
};
