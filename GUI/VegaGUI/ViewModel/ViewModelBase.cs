using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Diagnostics;
using FinancialPricingTool.DatabaseServices;
namespace FinancialPricingTool.ViewModel
{
    public abstract class ViewModelBase : INotifyPropertyChanged, IDisposable
    {
        protected ViewModelBase() {}

        public virtual string ViewName { get; protected set; }

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

        public void Dispose()
        {
            this.OnDispose();
        }

        protected virtual void OnDispose() { }
    }
}
