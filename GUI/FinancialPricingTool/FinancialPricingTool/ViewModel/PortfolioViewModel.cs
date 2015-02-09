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
            _bottomLeftUserControl = new OptionPricingViewModel();
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

        private PortfolioUserControl _bottomLeftUserControl;
        public PortfolioUserControl BottomLeftUserControl
        {
            get
            {
                return _bottomLeftUserControl;
            }
            set
            {
                _bottomLeftUserControl = value;
                base.OnPropertyChanged("BottomLeftUserControl");
            }
        }
    }
}
