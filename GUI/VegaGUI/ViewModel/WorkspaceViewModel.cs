using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinancialPricingTool.ViewModel
{
    public abstract class WorkspaceViewModel : ViewModelBase
    {
        protected WorkspaceViewModel() { }

        public event EventHandler RequestClose;

        void OnRequestClose()
        {
            EventHandler handler = this.RequestClose;
            if (handler != null)
            {
                handler(this, EventArgs.Empty);
            }
        }
    }
}
