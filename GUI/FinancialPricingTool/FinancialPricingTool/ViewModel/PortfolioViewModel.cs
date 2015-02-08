using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinancialPricingTool.ViewModel
{
    public class PortfolioViewModel : WorkspaceViewModel
    {
        public PortfolioViewModel()
        {
            base.ViewName = "Portfolio";
            Name = "New Portfolio";
        }

        private string _name;
        public virtual string Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
                base.OnPropertyChanged("Name");
            }
        }
    }
}
