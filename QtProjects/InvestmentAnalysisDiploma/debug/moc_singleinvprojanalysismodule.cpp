/****************************************************************************
** Meta object code from reading C++ file 'singleinvprojanalysismodule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../singleinvprojanalysismodule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'singleinvprojanalysismodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SingleInvProjAnalysisModule_t {
    QByteArrayData data[7];
    char stringdata[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleInvProjAnalysisModule_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleInvProjAnalysisModule_t qt_meta_stringdata_SingleInvProjAnalysisModule = {
    {
QT_MOC_LITERAL(0, 0, 27),
QT_MOC_LITERAL(1, 28, 20),
QT_MOC_LITERAL(2, 49, 0),
QT_MOC_LITERAL(3, 50, 13),
QT_MOC_LITERAL(4, 64, 23),
QT_MOC_LITERAL(5, 88, 24),
QT_MOC_LITERAL(6, 113, 12)
    },
    "SingleInvProjAnalysisModule\0"
    "theoreticalAnalysing\0\0realAnalysing\0"
    "investmentRiskAnalysing\0"
    "sensetivityRiskAnalysing\0bepAnalysing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleInvProjAnalysisModule[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SingleInvProjAnalysisModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SingleInvProjAnalysisModule *_t = static_cast<SingleInvProjAnalysisModule *>(_o);
        switch (_id) {
        case 0: _t->theoreticalAnalysing(); break;
        case 1: _t->realAnalysing(); break;
        case 2: _t->investmentRiskAnalysing(); break;
        case 3: _t->sensetivityRiskAnalysing(); break;
        case 4: _t->bepAnalysing(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SingleInvProjAnalysisModule::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SingleInvProjAnalysisModule.data,
      qt_meta_data_SingleInvProjAnalysisModule,  qt_static_metacall, 0, 0}
};


const QMetaObject *SingleInvProjAnalysisModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleInvProjAnalysisModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SingleInvProjAnalysisModule.stringdata))
        return static_cast<void*>(const_cast< SingleInvProjAnalysisModule*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SingleInvProjAnalysisModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
