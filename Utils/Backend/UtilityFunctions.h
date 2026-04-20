#include "Headers/vars.h"
#include "pointerFuncs.h"

#include <random>


std::string randHex() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 15);
    std::stringstream ss;
    for (int i = 0; i < 8; ++i) {
        ss << std::hex << dist(rd);
    }
    return ss.str();
}

int get_TimeStamp()
{
    std::time_t timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return static_cast<int>(timenow);
}

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(rng);
}


template<typename _T>
void IL2CPP_CHECKTYPE(std::string& type)
{
    if (std::is_same_v<_T, int> || std::is_same_v<_T, size_t>) type += "Int32";
    else if (std::is_same_v<_T, float> || std::is_same_v<_T, double>) type += "Single";
    else if (std::is_same_v<_T, monoString*>) type += "String";
    else type += "Object";
}






// Structs \\

class UnityThread
{
public:
    Il2CppThread* Thread = nullptr;
    bool Active = true;
    UnityThread() : Thread(il2cpp_thread_attach(il2cpp_domain_get())) {}

    void Start()
    {
        if (Thread == nullptr)
            Thread = il2cpp_thread_attach(il2cpp_domain_get());
    }

    void End()
    {
        if (Thread != nullptr) {
            il2cpp_thread_detach(Thread);
            Thread = nullptr;
        }
    }

    // I dont recommend using this, it's actually so useless
    void Sleep(int milliSeconds)
    {
        if (il2cpp_thread_current() == Thread) {
            Pointer<void(int)>_sleep(mscorlib->Class(OBF("System.Threading.Thread"))->Method(OBF("Sleep"))->VA());
            _sleep(milliSeconds);
        }
    }

    static void _Thread(UnityThread* unityThread, std::function<void()>CodeInLoop)
    {
        unityThread->Start();
        while (true)
        {
            CodeInLoop();
        }
        unityThread->End();
    }

private:
    BNM::Image* mscorlib = BNM::Domain().Assembly("mscorlib")->Image();
};
#define UNITY_CREATE_THREAD(yourThread, ThreadVarName, StdFunctionCode) std::thread ThreadVarName(UnityThread::_Thread, yourThread, StdFunctionCode); ThreadVarName.detach()


struct Object : Il2CppObject { // useless shit. Made this months ago

    std::string ToString()
    {
        return Json::Encode((BNM::Object*)this)->ToString();
    }

    static Object* New(const char* objStr)
    {
        return (Object*)Json::Decode(MonoString::New(objStr));
    }

};

template<typename TKey, typename TValue>
struct Il2CppDictionary
{
public:

    BNM::Image* mscorlib = BNM::Domain().Assembly("mscorlib")->Image();
    BNM::Class* inflatedKlass;

    Il2CppDictionary(std::string type1, std::string type2)
    {
        inflatedKlass = mscorlib->Class(OBF("System.Collections.Generic.Dictionary`2"))->Inflate({ mscorlib->Class(type1.c_str()),mscorlib->Class(type2.c_str()) });
        tType1 = type1; tType2 = type2;
        Dict = BNM::Object::New(inflatedKlass);
    }

    BNM::Object* get_Dict()
    {
        return Dict;
    }

    void set_Dict(BNM::Object* dict)
    {
        Dict = dict;
    }

    int Size() {
        BNM::Method* get_Count_Method = Dict->Class()->Method("get_Count");
        static const auto get_Count = (int (*)(void*))get_Count_Method->VA();
        return get_Count(Dict);
    }

    void Clear() {
        static const auto fn = (void (*)(void*))Dict->Class()->Method("Clear")->VA();
        fn(Dict);
    }

    void EditValue(TKey valueKey, TValue newvalue) {
        BNM::Method* sex_m = Dict->Class()->Method(OBF("set_Item"));
        static const auto sex = (void (*)(void*, TKey, TValue, void*))((void*)sex_m->VA());
        sex((void*)Dict, valueKey, newvalue, (void*)sex_m);
    }

    void Add(TKey key, TValue value) {
        BNM::Method* Add_method = Dict->Class()->Method(OBF("Add"));
        static const auto Add = (void (*)(void*, TKey, TValue, void*))((void*)Add_method->VA());
        Add((void*)Dict, key, value, (void*)Add_method);
    }

    void Remove(TKey key) {
        BNM::Method* remove_method = Dict->Class()->Method(OBF("Remove"));
        static const auto remove = (void (*)(void*, TKey, void*))((void*)remove_method->VA());
        remove((void*)Dict, key, (void*)remove_method);
    }

    TValue get_Item(TKey key)
    {
        BNM::Method* get_method = Dict->Class()->Method(OBF("get_Item"));
        static const auto get = (TValue(*)(void*, TKey, void*))((void*)get_method->VA());
        return get((void*)Dict, key, (void*)get_method);
    }

    static Il2CppDictionary<TKey, TValue> GetDict(BNM::Object* dict) {
        auto _Dict = Il2CppDictionary<TKey, TValue>("System.String", "System.String"); _Dict.set_Dict(dict);
        return _Dict;
    }

    std::string ToString()
    {
        return Json::Encode(Dict)->ToString();
    }

private:
    BNM::Object* Dict;
    std::string tType1;
    std::string tType2;
};


template<typename T>
class SxIl2CppList
{
public:
    BNM::Image* mscorlib = BNM::Domain().Assembly(OBF("mscorlib"))->Image();
    std::string GenericType = "System.";

    SxIl2CppList()
    {
        IL2CPP_CHECKTYPE<T>(GenericType);
        List = mscorlib->Class(OBF("System.Collections.Generic.List`1"))->Inflate({ mscorlib->Class(GenericType.c_str()) });
        RealList = il2cpp_object_new((Il2CppClass*)List);
        MethodInfo* Constructor = (MethodInfo*)List->Method(OBF(".ctor"));
        il2cpp_runtime_invoke(Constructor, RealList, nullptr, nullptr);
    }

    SxIl2CppList(std::initializer_list<T> init) : SxIl2CppList()
    {
        for (const T& item : init)
            push_back(item);
    }

    SxIl2CppList(Il2CppArray* _array) : SxIl2CppList()
    {
        Il2CppClass* weikmfemfe = (Il2CppClass*)List;
        const MethodInfo* _method = weikmfemfe->methods[0x2];
        Pointer<void(void*, void*, const MethodInfo*)>__method((uint64_t)_method->methodPointer);
        __method(RealList, _array, _method);
    }

    SxIl2CppList(const char* JsonString) : SxIl2CppList() { _INIT_(JsonString); }
    SxIl2CppList(json Json) : SxIl2CppList() { _INIT_(Json.dump().c_str()); }
    SxIl2CppList(ojson Json) : SxIl2CppList() { _INIT_(Json.dump().c_str()); }


    SxIl2CppList& operator=(std::vector<T> _list)
    {
        clear();
        for (int i = 0; i < _list.size(); i++)
            push_back(_list[i]);

        return *this;
    }

    SxIl2CppList& operator=(const char* JsonString) { _INIT_(JsonString); return *this; }
    SxIl2CppList& operator=(json Json)  { _INIT_(Json.dump().c_str()); return *this; }
    SxIl2CppList& operator=(ojson Json) { _INIT_(Json.dump().c_str()); return *this; }

    Il2CppObject* operator()() { return RealList; }
    void operator()(Il2CppObject* newList) { List = (BNM::Class*)newList->Il2CppClass.klass; RealList = newList; }

    operator Il2CppObject*() const { return RealList; }
    operator BNM::Object* () const { return RealList; }
    operator void*()         const { return RealList; }

    size_t       size() { return _Call_<size_t>(OBF("get_Count")); }
    size_t       capacity() { return _Call_<size_t>(OBF("get_Capacity")); }
    bool         empty() { return size() ? true : false; }
    bool         contains(T item) { return _Call_<bool, T>(OBF("Contains"), item); }
    void         clear() { _Call_<void>(OBF("Clear")); }
    T            at(int ItemIndex) { return _Call_<T, int>(OBF("get_Item"), ItemIndex); }
    void         at(int ItemIndex, T newValue) { _Call_<void, int, T>(OBF("set_Item"), ItemIndex, newValue); }
    void         push_back(T item) { _Call_<void, T>(OBF("Add"), item); }
    bool         remove(T item) { return _Call_<bool, T>(OBF("Remove"), item); }
    void         removeAt(int ItemIndex) { _Call_<void, int>(OBF("RemoveAt"), ItemIndex); }
    void         removeRange(int start, int end) { _Call_<void, int, int>(OBF("RemoveRange"), start, end); }
    void         sort() { _Call_<void>(OBF("Sort")); }
    void         reverse() { _Call_<void>(OBF("Reverse")); }
    Il2CppArray* ToArray() { return _Call_<Il2CppArray*>(OBF("ToArray")); }
    ojson        JSON() { return ojson::parse(Json::SerializeObject(RealList)->ToString()); }
    std::string  ToString(bool prettyPrint = false) { return ojson::parse(Json::SerializeObject(RealList)->ToString()).dump(prettyPrint ? 3 : -1); }

    // difference between at and operator[]:
    // -> operator[] uses the _items field and at method uses get/set item method instead (I suggest using at method, operator[] isn't really precise)
    T operator[](size_t index) const { return (T)GET_FIELD(Il2CppArray*, RealList + RealList->Il2CppClass.klass->fields[0x1].offset)->vector[index]; }
    T& operator[](size_t index) {
        Il2CppArray* nigger = GET_FIELD(Il2CppArray*, RealList + RealList->Il2CppClass.klass->fields[0x1].offset);
        return (T&)nigger->vector[index];
    }

    // Foreach = lambda must return bool (for loop: true = continue, false = break)
    // foreach = just normal void lol
    void Foreach(std::function<bool(T, size_t)>func) {
        if (!func) return;
        for (size_t i = 0; i < size(); i++) {
            if (!func(at(static_cast<int>(i)), i)) {
                break;
            }
        }
    }

    void Foreach(std::function<bool(T)>func)         {  Foreach([func](T value, size_t) -> bool { return func(value); }); }
    void foreach(std::function<void(T, size_t)>func) {  Foreach([func](T value, size_t index) -> bool { func(value, index); return true; }); }
    void foreach(std::function<void(T)>func)         {  foreach([func](T value, size_t) { func(value); }); }

    static SxIl2CppList<T> GET(Il2CppObject* _list)
    {
        SxIl2CppList<T> MyList;
        MyList(_list);
        return MyList;
    }
private:
    BNM::Class* List;
    Il2CppObject* RealList;

    template <typename R, typename... Args>
    R _Call_(const char* ListMethodName, Args... args)
    {
        BNM::Method* _method = List->Method(ListMethodName);
        Pointer<R(void*, Args..., BNM::Method*)>__method(_method->VA());
        return __method(RealList, std::forward<Args>(args)..., _method);
    }

    void _INIT_(const char* str)
    {
        RealList = (Il2CppObject*)Json::DeserializeObject(MonoString::New(str), Type__GetType(MonoString::New((OBF("System.Collections.Generic.List`1[") + GenericType + "]").c_str())));
        List = (BNM::Class*)RealList->Il2CppClass.klass;
    }
};


typedef struct Packet Packet;
typedef struct ByteArray ByteArray;
typedef struct EncryptData EncryptData;
typedef struct SocketManager SocketManager;
typedef struct Socket Socket;

#define __CREATE_CALL__(ths, __MethodType__, klasss, __method__, __method_addr__) \
        __MethodType__ _method = klasss->__method__; \
        Pointer<R(void*, Args..., __MethodType__)>__method((uint64_t)__method_addr__); \
        return __method(ths, std::forward<Args>(args)..., _method)

struct Packet {
    static Packet* New()                            { return (Packet*)il2cpp_object_new(GET_CLASS(___skibidi::______aa_____));                     }
    int get_AttachmentCount()                       { return _Call_<int>(OBF("get_AttachmentCount"));                                                   }
    void set_AttachmentCount(int value)             {        _Call_<void, int>(OBF("set_AttachmentCount"), value);                                      }
    int get_Id()                                    { return _Call_<int>(OBF("get_Id"));                                                                }
    void set_Id(int value)                          {        _Call_<void, int>(OBF("set_Id"), value);                                                   }
    std::string get_Namespace()                     { return _Call_<monoString*>(OBF("get_Namespace"))->ToString();                                     }
    void set_Namespace(const char* value)           {        _Call_<void, monoString*>(OBF("set_Namespace"), MonoString::New(value));                   }
    std::string get_Payload()                       { return _Call_<monoString*>(OBF("get_Payload"))->ToString();                                       }
    void set_Payload(const char* value)             {        _Call_<void, monoString*>(OBF("set_Payload"), MonoString::New(value));                     }
    std::string get_EventName()                     { return _Call_<monoString*>(OBF("get_EventName"))->ToString();                                     }
    void set_EventName(const char* value)           {        _Call_<void, monoString*>(OBF("set_EventName"), MonoString::New(value));                   }
    std::string Encode()                            { return _Call_<monoString*>(OBF("Encode"))->ToString();                                            }
    void* EncodeBinary()                            { return _Call_<void*>(OBF("EncodeBinary"));                                                        }
    Packet* Clone()                                 {        _Call_<Packet*>(OBF("Clone"));                                                             }
    std::string ToString(bool prettyPrint = false)  { return ojson::parse(_Call_<monoString*>(OBF("ToString"))->ToString()).dump(prettyPrint ? 3 : -1); }
private:
    template <typename R, typename... Args>
    R _Call_(const char* MethodName, Args... args)
    {
        __CREATE_CALL__(this, BNM::Method*, BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image()->Class(OBF("BestHTTP.SocketIO.Packet")), Method(MethodName), _method->VA());
    }
};


struct ByteArray {
    std::string       ToString() { return wfwefegergej::_(this)->ToString(); }
    static ByteArray* New(const char* str) { return (ByteArray*)wfwefegergej::__(str); }
};

struct EncryptData {
    ByteArray* Decrypt(ByteArray* EncryptedData)                  { return _Call_<ByteArray*, ByteArray*>(0x1, EncryptedData); }
    ByteArray* Encrypt(ByteArray* ByteArrData, bool idfk = false) { return _Call_<ByteArray*, ByteArray*, bool>(0x2, ByteArrData, idfk); }
private:
    template <typename R, typename... Args>
    R _Call_(int methodIndex, Args... args)
    {
        __CREATE_CALL__(this, const MethodInfo*, GET_CLASS(___skibidi::______aa______), methods[methodIndex], _method->methodPointer);
    }
};

struct SocketManager {
    void*        get_Uri() { return _Call_<void*>(OBF("get_Uri")); }
    Socket*      get_Socket() { return _Call_<Socket*>(OBF("get_Socket")); }
    Socket*      get_Item(const char* nsp) { return _Call_<Socket*, monoString*>(OBF("get_Item"), MonoString::New(nsp)); }
    EncryptData* get_Extras() { return _Call_<EncryptData*>(OBF("get_Extras")); }
    void         SendOfflinePackets() { _Call_<void>(OBF("SendOfflinePackets")); }
    int          get_NextAckId() { return _Call_<int>(OBF("get_NextAckId")); }
    void         Open()  { _Call_<void>(OBF("Open")); }
    void         Close() { _Call_<void>(OBF("Close")); }
    std::string  ToString() { return _Call_<monoString*>(OBF("ToString"))->ToString(); }
private:
    template <typename R, typename... Args>
    R _Call_(const char* MethodName, Args... args)
    {
        __CREATE_CALL__(this, BNM::Method*, BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image()->Class(OBF("BestHTTP.SocketIO.SocketManager")), Method(MethodName), _method->VA());
    }
};

struct Socket {
    SocketManager* get_Manager() { return _Call_<SocketManager*>(OBF("get_Manager")); }
    void           set_Manager(SocketManager* SM) { _Call_<void, SocketManager*>(OBF("set_Manager"), SM); }
    std::string    get_Namespace() { return _Call_<monoString*>(OBF("get_Namespace"))->ToString(); }
    void           set_Namespace(monoString* nsp) { _Call_<void, monoString*>(OBF("set_Namespace"), nsp); }
    std::string    get_Id() { return _Call_<monoString*>(OBF("get_Id"))->ToString(); }
    void           set_Id(monoString* value) { _Call_<void, monoString*>(OBF("set_Id"), value); }
    bool           get_IsOpen() { return _Call_<bool>(OBF("get_IsOpen")); }
    void           set_IsOpen(bool value) { _Call_<void, bool>(OBF("set_IsOpen"), value); }
    bool           get_AutoDecodePayload() { return _Call_<bool>(OBF("get_AutoDecodePayload")); }
    void           set_AutoDecodePayload(bool value) { _Call_<void, bool>(OBF("set_AutoDecodePayload"), value); }
    void           Open() { _Call_<void>(OBF("BestHTTP.SocketIO.ISocket.Open")); }
    void           Disconnect() { _Call_<void>(OBF("Disconnect")); }
    Socket*        Emit(const char* EN, const char* data) { SxIl2CppList<void*> list = { Json::Decode(MonoString::New(data)) }; return _Call_<Socket*, monoString*, Il2CppArray*>(OBF("Emit"), MonoString::New(EN), list.ToArray()); }
    Socket*        EmitAck(Packet* oP, const char* data) { SxIl2CppList<void*> list = { Json::Decode(MonoString::New(data)) }; return _Call_<Socket*, Packet*, Il2CppArray*>(OBF("EmitAck"), oP, list.ToArray()); }
    void           OnPacket(Packet* packet) { _Call_<void, Packet*>(OBF("BestHTTP.SocketIO.ISocket.OnPacket"), packet); }
private:
    template <typename R, typename... Args>
    R _Call_(const char* MethodName, Args... args)
    {
        __CREATE_CALL__(this, BNM::Method*, BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image()->Class(OBF("BestHTTP.SocketIO.Socket")), Method(MethodName), _method->VA());
    }
};

class WebsocketManager {
public:
    // what you can also do is WebsocketManager* WebsocketManager::New();
    WebsocketManager()
    {
        BNM::Image* assemblyC = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image();
        BNM::Class* Singleton = assemblyC->Class(OBF("Rilisoft.Singleton`1"))->Inflate({ assemblyC->Class(OBF("Rilisoft.WebSocket.WebSocketManager")) });
        BNM::Method* meth = Singleton->Method(OBF("get_Instance"));
        Pointer<void* (BNM::Method*)>get_Instance(meth->VA());
        Instance = (Il2CppObject*)get_Instance(meth);
        Klass = Instance->Il2CppClass.klass;
    }

    operator Il2CppObject* () const { return Instance; }
    operator void* () const { return (void*)Instance; }
    operator uint64_t () const { return (uint64_t)Instance; }

    SocketManager*get_SocketManager()                 { return _Call_<SocketManager*>(0x0); }
    void          set_SocketManager(SocketManager* SM){        _Call_<void, SocketManager*>(0x1, SM); }
    std::string   get_ServerURL()                     { return _Call_<monoString*>(0x4)->ToString(); }
    void          set_SocketManager(const char* nsp)  {        _Call_<void, monoString*>(0x5, MonoString::New(nsp)); }
    Socket*       get_Socket()                        { return _Call_<Socket*>(0x6); }
    void          auth_v2()                           {        _Call_<void>(0xf); }
    void          send_EventName(const char* EN)      {        _Call_<void, monoString*>(0x13, MonoString::New(EN)); }
    bool          send_request(const char* EN, const char* data)      { return _Call_<bool, monoString*, void*, void*>(0x14, MonoString::New(EN), (void*)Json::Decode(MonoString::New(data)), nullptr); }
    int           send_EventName_v2(const char* EN)   { return _Call_<int, monoString*>(0x15, MonoString::New(EN)); }
    int           get_LatestReqId()                   { return GET_FIELD(int, (uint64_t)Instance + 38); }
private:
    Il2CppClass* Klass;
    Il2CppObject* Instance;

    template <typename R, typename... Args>
    R _Call_(int methodIndex, Args... args)
    {
        __CREATE_CALL__(Instance, const MethodInfo*, Klass, methods[methodIndex], _method->methodPointer);
    }
};


struct ejfwjdfnef // WebsocketPacket
{
public:
    std::string Data;

    void* get_Packet()
    {
        return _eikfjnwfiejgefg;
    }

    void set_Packet(void* wdejfmwikfdmjergnejfg) // void* packet
    {
        _eikfjnwfiejgefg = (Il2CppObject*)wdejfmwikfdmjergnejfg;
    }

    void Clear()
    {
        dkfmwskfmejge::set_Payload(_eikfjnwfiejgefg, MonoString::New(""));
        dkfmwskfmejge::set_EventName(_eikfjnwfiejgefg, MonoString::New(""));
    }

    void RenewPacket()
    {
        _eikfjnwfiejgefg = il2cpp_object_new(GET_CLASS(___skibidi::______aa_____));
    }

    void SetData(const char* EventName, const char* data)
    {
        std::stringstream _idk;
        _idk << "[\"" << EventName << "\"," << data << "]";
        dkfmwskfmejge::set_EventName(_eikfjnwfiejgefg, MonoString::New(EventName));
        dkfmwskfmejge::set_Payload(_eikfjnwfiejgefg, MonoString::New(_idk.str().c_str()));
        Data = _idk.str();
    }

    std::string ToString(int method = 0) // available methods: 0, any other value
    {
        if (method == 0) return dkfmwskfmejge::ToString(_eikfjnwfiejgefg)->ToString();
        return Data;
    }

    static ejfwjdfnef ObtainPacket(void* owekdfiwikdekfie) // void* packet
    {
        ejfwjdfnef _; _.set_Packet(owekdfiwikdekfie); return _;
    }

private:
    Il2CppObject* _eikfjnwfiejgefg = il2cpp_object_new(GET_CLASS(___skibidi::______aa_____));
};


class ItemRecord {
public:
    ItemRecord(int eiofjewikfiegr) { __ = get_ItemRecord(eiofjewikfiegr); }
    ItemRecord(const char* eiofjewikfiegr) { __ = get_ItemRecord_Str(MonoString::New(eiofjewikfiegr)); }

    std::string String() { return _CallStr_(OBF("get_Tag"))->ToString(); }
    std::string Name() { return _CallStr_(OBF("get_shopName"))->ToString(); }
    std::string ToString() { return _CallStr_(OBF("ToString"))->ToString(); }

    int Index() { return _Call_<int>(OBF("get_Index")); }
    int GalleryIndex() { return _Call_<int>(OBF("get_WeaponNumber")); }
    int GetCategoryType() { return _Call_<int>(OBF("get_Category")); } // enum CategoryNames

    bool IsRoyale() { return _Call_<bool>(OBF("get_IsRoyale")); }
    bool IsCraft() { return _Call_<bool>(OBF("get_IsCraft")); }
    bool IsCraftFromSet() { return _Call_<bool>(OBF("get_IsCraftFromSet")); }
    bool IsClansCraft() { return _Call_<bool>(OBF("get_IsClansCraft")); }

    static ItemRecord GetRecord(int GalleryNumber) {
        for (int i = 1; i <= 2000; i++) {
            ItemRecord rec = ItemRecord(i * 1000 + 1);
            int gal = rec.GalleryIndex();
            if (gal == GalleryNumber) return rec;
        }
        return NULL;
    }

    static int GetIndex(int GalleryNumber) {
        return GetRecord(GalleryNumber).Index();
    }

    void* operator()() { return __; }
private:
    void* __; // ItemRecord instance
    BNM::Class* ___ = BNM::Domain().Assembly(OBF("Assembly-CSharp"))->Image()->Class(OBF("ItemRecord"));

    template <typename R, typename... Args>
    R _Call_(const char* ItemRecordMethodName, Args... args)
    {
        if (__ == nullptr) return 0;
        Pointer<R(void*, Args...)>__method(___->Method(ItemRecordMethodName)->VA());
        return __method(__, std::forward<Args>(args)...);
    }

    template <typename... Args>
    monoString* _CallStr_(const char* ItemRecordMethodName, Args... args)
    {
        if (__ == nullptr) return MonoString::New("");
        Pointer<monoString*(void*, Args...)>__method(___->Method(ItemRecordMethodName)->VA());
        return __method(__, std::forward<Args>(args)...);
    }
};


// Websocket Utilities

namespace WS {
    std::string GameVersion;

    namespace Utils {

        void* ListRequest(std::string requests)
        {
            std::stringstream output;
            output << OBF("{\"id\":63, \"i\":\"6e393aa0\", \"p\":{\"c\":[") << requests << OBF("]}}");
            return wfwefegergej::__(output.str().c_str());
        }

        void* SingleRequest(std::string request) {
            return wfwefegergej::__(request.c_str());
        }

        ojson __create(int id, ojson params, bool emptyParams = false, bool emptyU = false, bool UseiInstead = false)
        {
            std::string rh = randHex();
            ojson nigger = {
                {"id", id},
                {"ci", rh},
                {"p", json::object()},
                {"h", json::object()},
                //{"v", WS::GameVersion},
                {"u", json::array()},
            };

            if (!emptyParams) { nigger["p"] = params; }
            if (!emptyU) { nigger["u"] = { 0 }; }
            if (UseiInstead) { nigger.erase("ci"); nigger["i"] = rh; }
            
            return nigger;
        }

        ojson __singleCreate(int id, ojson params, bool emptyParams = false)
        {
            ojson wifjeif = __create(id, params, emptyParams, false, true);
            wifjeif.erase("u"); wifjeif.erase("h"); wifjeif.erase("v");
            return wifjeif;
        }

        ojson EmptyCommand() { return __create(106, {}, true); }

        std::string UpdateUtilityDictionaryValue(int UtilityValue, int value, int type = 1)
        {
            return WS::Utils::__create(67, {
                {std::to_string(type), {
                    {std::to_string(UtilityValue), value}
                }}
            }).dump();
        }

        std::string UpdateUtilityDictionaryValue(int UtilityValue, std::string value, int type = 1)
        {
            return WS::Utils::__create(67, {
                {std::to_string(type), {
                    {std::to_string(UtilityValue), value}
                }}
            }).dump();
        }

        bool AddRequest(const char* eventName, std::string data, int sendAmount = 1, bool SnapshotRequest = false, bool ReloadWhenReceived = vars::ReloadWhenReceived, bool NotifyWhenReceived = false, const char* ResponseReceivedName = "", ImGuiToastType toastType = ImGuiToastType::Info, bool ForceSuccessStatus = false, std::function<void(ojson, ojson)>OnRequestReceived = [](ojson _r, ojson _p){})
        {
            if (sendAmount < 1) return false;
            std::stringstream req;
            if (SnapshotRequest) req << OBF("{\"id\":63, \"i\":\"") << randHex() << OBF("\", \"p\":{\"c\":[") << data << OBF("]}}");
            else req << data;
            ojson ieifeifk;
            try {
                ieifeifk = ojson::parse(req.str());
            }
            catch (ojson::parse_error& e) {
                Sxitxma::SetColor(ConsoleColor::BrightRed);
                std::cout << e.what() << OBF("\n");
                std::cout << req.str() << OBF("\n\n\n");
                Sxitxma::ResetColor();
                return false;
            }
            if (ieifeifk[OBF("req_id")].is_null()) { ieifeifk[OBF("req_id")] = generateRandomNumber(93473484, 123473484); }

            vars::WebsocketSendRequest.push_back([ieifeifk, eventName, sendAmount](const char*& _eN, int& _sA) { _sA = sendAmount; _eN = eventName; vars::SendRequestData = ieifeifk;});
            vars::WSResponses.push_back({std::string(eventName),ieifeifk.dump(),ReloadWhenReceived, NotifyWhenReceived,ResponseReceivedName,toastType,ForceSuccessStatus,OnRequestReceived});
            return true;
        }

        void ReloadGame(bool Notify = true) {
            vars::AlwaysUpdateSlotsWhenRequestSent = false;
            vars::SendRequest = AddRequest(OBF("update_progress"), OBF("{\"i\":\"") + randHex() + OBF("\"}"), 1, false, false, Notify, OBF("Reload Game"), ImGuiToastType::Info, true, [](ojson _r, ojson _p){
                vars::AlwaysUpdateSlotsWhenRequestSent = true;
            });
        }

        void NotifyRequestSent(const char* requestName, int notifyLength = 2000)
        {
            if (vars::SendRequest) ImGui::InsertNotification({ ImGuiToastType::Success, notifyLength, OBF("Sent Request: %s"), requestName });
            else ImGui::InsertNotification({ ImGuiToastType::Error, notifyLength, OBF("Failed to Send Request: %s"), requestName});
        }

    }


    namespace Slots
    {
        ojson Pets;
        ojson Royale;
        ojson RoyaleCars;
        ojson Gadgets;
        ojson Wears;
        ojson Armors;
        ojson Tutorial;
        ojson Weapons;
        ojson LobbyItems;
        ojson ModulesInfo = ojson::object();

        bool Initialize = false;
        //bool OnetimeInitialize = false;

        void INIT(bool DontNotify = true, const char* RequestName = OBF("Initialize Slots"))
        {
            std::stringstream ___;
            ___ << OBF("{\"player_id\":\"") << iwsdmwoifmefgujerf()->ToString().c_str() << OBF("\"}");
            vars::SendRequest = WS::Utils::AddRequest(OBF("get_progress"), ___.str(), 1, false, false, DontNotify ? false : true, RequestName);
            WS::Slots::Initialize = vars::SendRequest;
        }
    }

}


void QuickMenuSend(const char* eventName, std::string data, const char* RequestName, bool Snapshot = true, bool ReloadWhenReceived = vars::ReloadWhenReceived, std::function<void(ojson, ojson)>OnRequestReceived = [](ojson Request, ojson Packet) {})
{
    vars::SendRequest = WS::Utils::AddRequest(eventName, data, 1, Snapshot, ReloadWhenReceived, true, RequestName, ImGuiToastType::Info, false, OnRequestReceived);
    WS::Utils::NotifyRequestSent(RequestName);
}