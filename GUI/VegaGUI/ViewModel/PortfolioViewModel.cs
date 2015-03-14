using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinancialPricingTool.CLR;
using FinancialPricingTool.Model;
namespace FinancialPricingTool.ViewModel
{
    public class PortfolioViewModel : WorkspaceViewModel
    {
        public PortfolioViewModel()
        {
            base.ViewName = "Portfolio";
            _portfolio = new PortfolioModel();

            Name = "New Portfolio";
            initPanels();
        }

        public PortfolioViewModel(PortfolioModel model)
        {
            base.ViewName = "Portfolio";
            _portfolio = model;
           initPanels();
        }

        private void initPanels() {
            _topLeftUserControl = new OptionPricePlotViewModel();
            _bottomLeftUserControl = new OptionPricingViewModel(_topLeftUserControl as OptionPricePlotViewModel);
            _bottomRightUserControl = new StocksViewModel();
        }

        private PortfolioModel _portfolio;

        public PortfolioModel GetPorfolioModel() { return _portfolio; }

        public virtual string Name
        {
            get
            {
                return _portfolio.Name;
            }
            set
            {
                _portfolio.Name = value;
                base.OnPropertyChanged("Name");
            }
        }
        private PortfolioUserControl _topLeftUserControl;
        public PortfolioUserControl TopLeftUserControl
        {
            get
            {
                return _topLeftUserControl;
            }
            set
            {
                _topLeftUserControl = value;
                base.OnPropertyChanged("TopLeftUserControl");
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

        private PortfolioUserControl _bottomRightUserControl;
        public PortfolioUserControl BottomRightUserControl
        {
            get
            {
                return _bottomRightUserControl;
            }
            set
            {
                _bottomRightUserControl = value;
                base.OnPropertyChanged("BottomRightUserControl");
            }
        }
        
    }
}
