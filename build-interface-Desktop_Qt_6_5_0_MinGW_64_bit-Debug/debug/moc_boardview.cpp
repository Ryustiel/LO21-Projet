/****************************************************************************
** Meta object code from reading C++ file 'boardview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interface/head_view/boardview.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'boardview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSVuePartieENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVuePartieENDCLASS = QtMocHelpers::stringData(
    "VuePartie",
    "actioncarte",
    "",
    "VueCarte*",
    "vc",
    "actionborne",
    "VueBorne*",
    "vb"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVuePartieENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[10];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[3];
    char stringdata5[12];
    char stringdata6[10];
    char stringdata7[3];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVuePartieENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVuePartieENDCLASS_t qt_meta_stringdata_CLASSVuePartieENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "VuePartie"
        QT_MOC_LITERAL(10, 11),  // "actioncarte"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 9),  // "VueCarte*"
        QT_MOC_LITERAL(33, 2),  // "vc"
        QT_MOC_LITERAL(36, 11),  // "actionborne"
        QT_MOC_LITERAL(48, 9),  // "VueBorne*"
        QT_MOC_LITERAL(58, 2)   // "vb"
    },
    "VuePartie",
    "actioncarte",
    "",
    "VueCarte*",
    "vc",
    "actionborne",
    "VueBorne*",
    "vb"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVuePartieENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x08,    1 /* Private */,
       5,    1,   29,    2, 0x08,    3 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject VuePartie::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSVuePartieENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVuePartieENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVuePartieENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VuePartie, std::true_type>,
        // method 'actioncarte'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<VueCarte *, std::false_type>,
        // method 'actionborne'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<VueBorne *, std::false_type>
    >,
    nullptr
} };

void VuePartie::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VuePartie *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->actioncarte((*reinterpret_cast< std::add_pointer_t<VueCarte*>>(_a[1]))); break;
        case 1: _t->actionborne((*reinterpret_cast< std::add_pointer_t<VueBorne*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< VueCarte* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< VueBorne* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *VuePartie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VuePartie::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVuePartieENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VuePartie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS = QtMocHelpers::stringData(
    "VuePartieTactique"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS_t qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS = {
    {
        QT_MOC_LITERAL(0, 17)   // "VuePartieTactique"
    },
    "VuePartieTactique"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVuePartieTactiqueENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject VuePartieTactique::staticMetaObject = { {
    QMetaObject::SuperData::link<VuePartie::staticMetaObject>(),
    qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVuePartieTactiqueENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VuePartieTactique, std::true_type>
    >,
    nullptr
} };

void VuePartieTactique::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *VuePartieTactique::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VuePartieTactique::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVuePartieTactiqueENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return VuePartie::qt_metacast(_clname);
}

int VuePartieTactique::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VuePartie::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
