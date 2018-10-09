#ifdef __cplusplus
extern "C" {
#endif //


   void AddCommand(const char* cmdName, PyObject* cmd);
    PyObject* GetCommand(const char* cmdName);

#ifdef __cplusplus
}
#endif //
