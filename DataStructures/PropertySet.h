#ifndef PROPERTY_SET_H
#define PROPERTY_SET_H

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Property.h"

template <class Name = std::string, class Value = double>
class PropertySet {
    public:
        typedef std::unordered_map<Name, Value> Map;
        PropertySet() : _name(), _map() {}
        PropertySet(const Name& name) : _name(name), _map() {}
        PropertySet(const Name& name, const Map& map) : _name(name), _map(map) {}

        void add(const Property<Name, Value>& property);
        void add(const Name& name, const Value& value);
        void remove(const Property<Name, Value>& property);
        void remove(const Name& name);

        typedef typename Map::iterator iterator;
        typedef typename Map::const_iterator const_iterator;
        iterator begin() { return _map.begin(); }
        const_iterator begin() const { return _map.begin(); }
        iterator end() { return _map.end(); }
        const_iterator end() const { return _map.end(); }

        Value& operator[](const Name& index) { return _map[index]; };
        const Value& operator[](const Name& index) const { return (_map.find(index))->second; };
    private:
        Name _name;
        Map _map;
};

template <class Name, class Value>
void PropertySet<Name,Value>::add(const Property<Name, Value>& property) {
    _map.insert(std::make_pair(property.name(), property.value()));
}

template <class Name, class Value>
void PropertySet<Name,Value>::add(const Name& name, const Value& value) {
    _map.insert(std::make_pair(name, value));
}

template <class Name, class Value>
void PropertySet<Name,Value>::remove(const Name& name) {
    _map.erase(name);
}

template <class Name, class Value>
void PropertySet<Name,Value>::remove(const Property<Name, Value>& property) {
    remove(property.getName());
}

#endif
