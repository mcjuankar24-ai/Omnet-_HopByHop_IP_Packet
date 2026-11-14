//
// Generated file, do not edit! Created by opp_msgtool 6.5 from paqueteIP.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "paqueteIP_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// std::vector<bool> elements are proxy objects (also for const access in libc++), so pack/unpack via a temporary
template<typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<bool,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++) {
        bool x = v[i];
        doParsimPacking(buffer, x);
    }
}

template<typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<bool,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++) {
        bool x;
        doParsimUnpacking(buffer, x);
        v[i] = x;
    }
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// Returns the string form of t produced by operator<<, or the given fallback string if there is no operator<<.
// (The fallback should be "" for compound types, whose fields can be displayed, and "(unprintable)" otherwise.)
template<typename T>
std::string toStringIfPrintable(const T& t, const char *fallback) {
    if constexpr (omnetpp::internal::is_printable<T>::value) {
        std::ostringstream os;
        os << t;
        return os.str();
    }
    return fallback;
}

template<typename T>
bool fromStringIfExtractable(T& t, const char *s) {
    if constexpr (omnetpp::internal::is_extractable<T>::value) {
        std::istringstream is(s);
        is >> t;
        return true;
    }
    return false;
}

Register_Class(paqueteIP)

paqueteIP::paqueteIP(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

paqueteIP::paqueteIP(const paqueteIP& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

paqueteIP::~paqueteIP()
{
}

paqueteIP& paqueteIP::operator=(const paqueteIP& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void paqueteIP::copy(const paqueteIP& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->tipoServicio = other.tipoServicio;
    this->tipoPaquete = other.tipoPaquete;
    this->FECprefijo = other.FECprefijo;
    this->FECmascara = other.FECmascara;
    this->etiquetaElegida = other.etiquetaElegida;
    for (size_t i = 0; i < 10; i++) {
        this->camino[i] = other.camino[i];
    }
    this->tiempo = other.tiempo;
}

void paqueteIP::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->tipoServicio);
    doParsimPacking(b,this->tipoPaquete);
    doParsimPacking(b,this->FECprefijo);
    doParsimPacking(b,this->FECmascara);
    doParsimPacking(b,this->etiquetaElegida);
    doParsimArrayPacking(b,this->camino,10);
    doParsimPacking(b,this->tiempo);
}

void paqueteIP::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->tipoServicio);
    doParsimUnpacking(b,this->tipoPaquete);
    doParsimUnpacking(b,this->FECprefijo);
    doParsimUnpacking(b,this->FECmascara);
    doParsimUnpacking(b,this->etiquetaElegida);
    doParsimArrayUnpacking(b,this->camino,10);
    doParsimUnpacking(b,this->tiempo);
}

int paqueteIP::getSrcAddr() const
{
    return this->srcAddr;
}

void paqueteIP::setSrcAddr(int srcAddr)
{
    this->srcAddr = srcAddr;
}

int paqueteIP::getDestAddr() const
{
    return this->destAddr;
}

void paqueteIP::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

int paqueteIP::getTipoServicio() const
{
    return this->tipoServicio;
}

void paqueteIP::setTipoServicio(int tipoServicio)
{
    this->tipoServicio = tipoServicio;
}

int paqueteIP::getTipoPaquete() const
{
    return this->tipoPaquete;
}

void paqueteIP::setTipoPaquete(int tipoPaquete)
{
    this->tipoPaquete = tipoPaquete;
}

int paqueteIP::getFECprefijo() const
{
    return this->FECprefijo;
}

void paqueteIP::setFECprefijo(int FECprefijo)
{
    this->FECprefijo = FECprefijo;
}

int paqueteIP::getFECmascara() const
{
    return this->FECmascara;
}

void paqueteIP::setFECmascara(int FECmascara)
{
    this->FECmascara = FECmascara;
}

int paqueteIP::getEtiquetaElegida() const
{
    return this->etiquetaElegida;
}

void paqueteIP::setEtiquetaElegida(int etiquetaElegida)
{
    this->etiquetaElegida = etiquetaElegida;
}

size_t paqueteIP::getCaminoArraySize() const
{
    return 10;
}

int paqueteIP::getCamino(size_t k) const
{
    if (k >= 10) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)10, (unsigned long)k);
    return this->camino[k];
}

void paqueteIP::setCamino(size_t k, int camino)
{
    if (k >= 10) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)10, (unsigned long)k);
    this->camino[k] = camino;
}

double paqueteIP::getTiempo() const
{
    return this->tiempo;
}

void paqueteIP::setTiempo(double tiempo)
{
    this->tiempo = tiempo;
}

class paqueteIPDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_destAddr,
        FIELD_tipoServicio,
        FIELD_tipoPaquete,
        FIELD_FECprefijo,
        FIELD_FECmascara,
        FIELD_etiquetaElegida,
        FIELD_camino,
        FIELD_tiempo,
    };
  public:
    paqueteIPDescriptor();
    virtual ~paqueteIPDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual std::string getValueAsString(omnetpp::any_ptr object) const override;
    virtual void setValueAsString(omnetpp::any_ptr object, const char *value) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(paqueteIPDescriptor)

paqueteIPDescriptor::paqueteIPDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(paqueteIP)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

paqueteIPDescriptor::~paqueteIPDescriptor()
{
    delete[] propertyNames;
}

bool paqueteIPDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<paqueteIP *>(obj)!=nullptr;
}

const char **paqueteIPDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *paqueteIPDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

std::string paqueteIPDescriptor::getValueAsString(omnetpp::any_ptr object) const
{
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    return ((cObject*)pp)->str();
}

void paqueteIPDescriptor::setValueAsString(omnetpp::any_ptr object, const char *value) const
{
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    if (!fromStringIfExtractable(*pp, value))
        cClassDescriptor::setValueAsString(object, value);
}

int paqueteIPDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int paqueteIPDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcAddr
        FD_ISEDITABLE,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_tipoServicio
        FD_ISEDITABLE,    // FIELD_tipoPaquete
        FD_ISEDITABLE,    // FIELD_FECprefijo
        FD_ISEDITABLE,    // FIELD_FECmascara
        FD_ISEDITABLE,    // FIELD_etiquetaElegida
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_camino
        FD_ISEDITABLE,    // FIELD_tiempo
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *paqueteIPDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "tipoServicio",
        "tipoPaquete",
        "FECprefijo",
        "FECmascara",
        "etiquetaElegida",
        "camino",
        "tiempo",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int paqueteIPDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "tipoServicio") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "tipoPaquete") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "FECprefijo") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "FECmascara") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "etiquetaElegida") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "camino") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "tiempo") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *paqueteIPDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_srcAddr
        "int",    // FIELD_destAddr
        "int",    // FIELD_tipoServicio
        "int",    // FIELD_tipoPaquete
        "int",    // FIELD_FECprefijo
        "int",    // FIELD_FECmascara
        "int",    // FIELD_etiquetaElegida
        "int",    // FIELD_camino
        "double",    // FIELD_tiempo
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **paqueteIPDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *paqueteIPDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int paqueteIPDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        case FIELD_camino: return 10;
        default: return 0;
    }
}

void paqueteIPDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'paqueteIP'", field);
    }
}

const char *paqueteIPDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string paqueteIPDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return long2string(pp->getSrcAddr());
        case FIELD_destAddr: return long2string(pp->getDestAddr());
        case FIELD_tipoServicio: return long2string(pp->getTipoServicio());
        case FIELD_tipoPaquete: return long2string(pp->getTipoPaquete());
        case FIELD_FECprefijo: return long2string(pp->getFECprefijo());
        case FIELD_FECmascara: return long2string(pp->getFECmascara());
        case FIELD_etiquetaElegida: return long2string(pp->getEtiquetaElegida());
        case FIELD_camino: return long2string(pp->getCamino(i));
        case FIELD_tiempo: return double2string(pp->getTiempo());
        default: return "";
    }
}

void paqueteIPDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: pp->setSrcAddr(string2long(value)); break;
        case FIELD_destAddr: pp->setDestAddr(string2long(value)); break;
        case FIELD_tipoServicio: pp->setTipoServicio(string2long(value)); break;
        case FIELD_tipoPaquete: pp->setTipoPaquete(string2long(value)); break;
        case FIELD_FECprefijo: pp->setFECprefijo(string2long(value)); break;
        case FIELD_FECmascara: pp->setFECmascara(string2long(value)); break;
        case FIELD_etiquetaElegida: pp->setEtiquetaElegida(string2long(value)); break;
        case FIELD_camino: pp->setCamino(i,string2long(value)); break;
        case FIELD_tiempo: pp->setTiempo(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'paqueteIP'", field);
    }
}

omnetpp::cValue paqueteIPDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return pp->getSrcAddr();
        case FIELD_destAddr: return pp->getDestAddr();
        case FIELD_tipoServicio: return pp->getTipoServicio();
        case FIELD_tipoPaquete: return pp->getTipoPaquete();
        case FIELD_FECprefijo: return pp->getFECprefijo();
        case FIELD_FECmascara: return pp->getFECmascara();
        case FIELD_etiquetaElegida: return pp->getEtiquetaElegida();
        case FIELD_camino: return pp->getCamino(i);
        case FIELD_tiempo: return pp->getTiempo();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'paqueteIP' as cValue -- field index out of range?", field);
    }
}

void paqueteIPDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: pp->setSrcAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destAddr: pp->setDestAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tipoServicio: pp->setTipoServicio(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tipoPaquete: pp->setTipoPaquete(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_FECprefijo: pp->setFECprefijo(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_FECmascara: pp->setFECmascara(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_etiquetaElegida: pp->setEtiquetaElegida(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_camino: pp->setCamino(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tiempo: pp->setTiempo(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'paqueteIP'", field);
    }
}

const char *paqueteIPDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr paqueteIPDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void paqueteIPDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    paqueteIP *pp = omnetpp::fromAnyPtr<paqueteIP>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'paqueteIP'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

