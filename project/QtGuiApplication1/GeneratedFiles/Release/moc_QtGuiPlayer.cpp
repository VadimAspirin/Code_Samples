/****************************************************************************
** Meta object code from reading C++ file 'QtGuiPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtGuiPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtGuiPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtGuiPlayer_t {
    QByteArrayData data[11];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGuiPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGuiPlayer_t qt_meta_stringdata_QtGuiPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QtGuiPlayer"
QT_MOC_LITERAL(1, 12, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 26), // "on_pushButtonPause_clicked"
QT_MOC_LITERAL(4, 64, 14), // "slotTimerAlarm"
QT_MOC_LITERAL(5, 79, 45), // "on_horizontalSliderCurrentFra..."
QT_MOC_LITERAL(6, 125, 46), // "on_horizontalSliderCurrentFra..."
QT_MOC_LITERAL(7, 172, 34), // "on_pushButtonForward1Frame_cl..."
QT_MOC_LITERAL(8, 207, 35), // "on_pushButtonForward10Frame_c..."
QT_MOC_LITERAL(9, 243, 35), // "on_pushButtonBackward1Frame_c..."
QT_MOC_LITERAL(10, 279, 36) // "on_pushButtonBackward10Frame_..."

    },
    "QtGuiPlayer\0on_pushButton_2_clicked\0"
    "\0on_pushButtonPause_clicked\0slotTimerAlarm\0"
    "on_horizontalSliderCurrentFrame_sliderPressed\0"
    "on_horizontalSliderCurrentFrame_sliderReleased\0"
    "on_pushButtonForward1Frame_clicked\0"
    "on_pushButtonForward10Frame_clicked\0"
    "on_pushButtonBackward1Frame_clicked\0"
    "on_pushButtonBackward10Frame_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGuiPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtGuiPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtGuiPlayer *_t = static_cast<QtGuiPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_2_clicked(); break;
        case 1: _t->on_pushButtonPause_clicked(); break;
        case 2: _t->slotTimerAlarm(); break;
        case 3: _t->on_horizontalSliderCurrentFrame_sliderPressed(); break;
        case 4: _t->on_horizontalSliderCurrentFrame_sliderReleased(); break;
        case 5: _t->on_pushButtonForward1Frame_clicked(); break;
        case 6: _t->on_pushButtonForward10Frame_clicked(); break;
        case 7: _t->on_pushButtonBackward1Frame_clicked(); break;
        case 8: _t->on_pushButtonBackward10Frame_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QtGuiPlayer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtGuiPlayer.data,
      qt_meta_data_QtGuiPlayer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtGuiPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGuiPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtGuiPlayer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QtGuiPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
