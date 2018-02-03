#include <Python.h>

#include "goacoin.h"

static PyObject *goacoin_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    goacoin_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    goacoin_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef GoaCoinMethods[] = {
    { "getPoWHash", goacoin_getpowhash, METH_VARARGS, "Returns the proof of work hash using goacoin hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef GoaCoinModule = {
    PyModuleDef_HEAD_INIT,
    "goacoin_hash",
    "...",
    -1,
    GoaCoinMethods
};

PyMODINIT_FUNC PyInit_goacoin_hash(void) {
    return PyModule_Create(&GoaCoinModule);
}

#else

PyMODINIT_FUNC initgoacoin_hash(void) {
    (void) Py_InitModule("goacoin_hash", GoaCoinMethods);
}
#endif
