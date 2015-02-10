#ifndef PROPERTY_H
#define PROPERTY_H

#include <String>

template <class Name = std::string, class Value = double>
class Property {
    public:
        Property();
        Property(const Name& name);
        Property(const Name& name, const Value& val);
        virtual ~Property();

        //Getters
        virtual Name name() const { return _name; }
        virtual Value value() const { return _value; }
        //Setters
        void setName(const Name& name) { _name = name; }
        void setValue(const Value& value) { _value = value; }

        Property<Name, Value>& operator=(const Property<Name, Value>& s);
        

    private:
        Name _name;
        Value _value;
};

#endif
