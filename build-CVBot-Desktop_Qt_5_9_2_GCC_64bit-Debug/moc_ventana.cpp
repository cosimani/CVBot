/****************************************************************************
** Meta object code from reading C++ file 'ventana.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CVBot/ventana.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ventana.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ventana_t {
    QByteArrayData data[11];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ventana_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ventana_t qt_meta_stringdata_Ventana = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Ventana"
QT_MOC_LITERAL(1, 8, 17), // "slot_activarBoton"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "columna"
QT_MOC_LITERAL(4, 35, 4), // "fila"
QT_MOC_LITERAL(5, 40, 14), // "slot_clicBoton"
QT_MOC_LITERAL(6, 55, 18), // "slot_recibirFrames"
QT_MOC_LITERAL(7, 74, 8), // "cv::Mat*"
QT_MOC_LITERAL(8, 83, 5), // "frame"
QT_MOC_LITERAL(9, 89, 23), // "slot_recibirFramesFondo"
QT_MOC_LITERAL(10, 113, 22) // "slot_despresionarBoton"

    },
    "Ventana\0slot_activarBoton\0\0columna\0"
    "fila\0slot_clicBoton\0slot_recibirFrames\0"
    "cv::Mat*\0frame\0slot_recibirFramesFondo\0"
    "slot_despresionarBoton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ventana[] = {

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
       1,    2,   39,    2, 0x08 /* Private */,
       5,    2,   44,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       9,    1,   52,    2, 0x08 /* Private */,
      10,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void Ventana::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Ventana *_t = static_cast<Ventana *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_activarBoton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_clicBoton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_recibirFrames((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 3: _t->slot_recibirFramesFondo((*reinterpret_cast< cv::Mat*(*)>(_a[1]))); break;
        case 4: _t->slot_despresionarBoton(); break;
        default: ;
        }
    }
}

const QMetaObject Ventana::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Ventana.data,
      qt_meta_data_Ventana,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Ventana::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ventana::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ventana.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Ventana::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
