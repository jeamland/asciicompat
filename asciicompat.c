#include <Python.h>

/* The empty Unicode object is shared to improve performance. */
static PyObject *asciistr_empty = NULL;

#define _Py_INCREF_ASCIISTR_EMPTY()                     \
    do {                                                \
        if (asciistr_empty != NULL)                     \
            Py_INCREF(asciistr_empty);                  \
        else {                                          \
            asciistr_empty = PyUnicode_New(0, 0);       \
            if (asciistr_empty != NULL) {               \
                Py_INCREF(asciistr_empty);              \
                assert(_PyUnicode_CheckConsistency(asciistr_empty, 1)); \
            }                                           \
        }                                               \
    } while (0)

#define _Py_RETURN_ASCIISTR_EMPTY()                     \
    do {                                                \
        _Py_INCREF_ASCIISTR_EMPTY();                    \
        return asciistr_empty;                          \
    } while (0)

static PyObject *
asciistr_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyObject *self = NULL;
    PyObject *x = NULL;
    Py_buffer view;
    static char *kwlist[] = {"object", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O:asciistr", kwlist, &x)) {
        return NULL;
    }
    if (x == NULL)
        _Py_RETURN_ASCIISTR_EMPTY();

    if (PyObject_CheckBuffer(x)) {
        if (PyObject_GetBuffer(x, &view, PyBUF_CONTIG_RO) < 0) {
            return NULL;
        }

        self = PyUnicode_FromString((char *)view.buf);
        PyBuffer_Release(&view);
    } else {
        self = PyObject_Str(x);
    }

    if (PyUnicode_KIND(self) != PyUnicode_1BYTE_KIND) {
        Py_DECREF(self);
        PyErr_SetString(PyExc_ValueError, "asciistr must contain no high-byte characters");
        return (NULL);
    }
    if (PyUnicode_MAX_CHAR_VALUE(self) > 127) {
        Py_DECREF(self);
        PyErr_SetString(PyExc_ValueError, "asciistr must contain no high-byte characters");
        return (NULL);
    }

    return self;
}

static PyObject *
asciistr_add(PyObject *v, PyObject *w)
{

    return Py_NotImplemented;
}

static PyNumberMethods asciistr_as_number = {
    asciistr_add             /* nb_add */
};

static int
asciistr_getbuffer(PyObject *exporter, Py_buffer *view, int flags)
{

    return (PyBuffer_FillInfo(view, exporter, PyUnicode_DATA(exporter),
        PyUnicode_GET_LENGTH(exporter), 1, flags));
}

static PyBufferProcs asciistr_as_buffer = {
    asciistr_getbuffer,      /* bf_getbuffer */
    0                        /* bf_releasebuffer */
};

static PyTypeObject asciistrType = {
    PyObject_HEAD_INIT(NULL)
    "asciistr",              /* tp_name */
    sizeof(PyUnicodeObject), /* tp_basicsize */
    0,                       /* tp_itemsize */
    0,                       /* tp_dealloc */
    0,                       /* tp_print */
    0,                       /* tp_getattr */
    0,                       /* tp_setattr */
    0,                       /* tp_reserved */
    0,                       /* tp_repr */
    &asciistr_as_number,     /* tp_as_number */
    0,                       /* tp_as_sequence */
    0,                       /* tp_as_mapping */
    0,                       /* tp_hash */
    0,                       /* tp_call */
    0,                       /* tp_str */
    0,                       /* tp_getattro */
    0,                       /* tp_setattro */
    &asciistr_as_buffer,     /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE, /* tp_flags */
    0,                       /* tp_doc */
    0,                       /* tp_traverse */
    0,                       /* tp_clear */
    0,                       /* tp_richcompare */
    0,                       /* tp_weaklistoffset */
    0,                       /* tp_iter */
    0,                       /* tp_iternext */
    0,                       /* tp_methods */
    0,                       /* tp_members */
    0,                       /* tp_getset */
    0,                       /* tp_base */
    0,                       /* tp_dict */
    0,                       /* tp_descr_get */
    0,                       /* tp_descr_set */
    0,                       /* tp_dictoffset */
    0,                       /* tp_init */
    0,                       /* tp_alloc */
    asciistr_new,            /* tp_new */
};

static PyModuleDef asciicompatmodule = {
    PyModuleDef_HEAD_INIT,
    "asciicompat",
    "asciicompat module",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_asciicompat(void)
{
    PyObject *m;

    asciistrType.tp_base = &PyUnicode_Type;
    if (PyType_Ready(&asciistrType) < 0)
        return NULL;

    m = PyModule_Create(&asciicompatmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&asciistrType);
    PyModule_AddObject(m, "asciistr", (PyObject *) &asciistrType);
    return m;
}
