using System.ComponentModel;

namespace FinancialPricingTool.Utilities
{
    public class Property : INotifyPropertyChanged
    {
        public Property(string key, object value)
        {
            Key = key;
            Value = value;
        }
        public string Key { get; set; }
        private object _value;
        public object Value
        {
            get
            {
                return _value;
            }
            set
            {
                _value = value;
                OnPropertyChanged("Value");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string property_name)
        {
            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (handler != null)
            {
                PropertyChangedEventArgs e = new PropertyChangedEventArgs(property_name);
                handler(this, e);
            }
        }
    }
}
