using System;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows.Data;
using FinancialPricingTool.DatabaseServices;
using FinancialPricingTool.Model;
namespace FinancialPricingTool.ViewModel
{
    public class MainWindowViewModel : WorkspaceViewModel
    {
        ObservableCollection<WorkspaceViewModel> _workspaces;
        WorkspaceViewModel _activeWorkspace;
        private DatabaseService _databaseService;
        public MainWindowViewModel()
        {
            base.ViewName = "Financial Pricing Tool";

            _databaseService = new DatabaseService();
            ObservableCollection<PortfolioModel> dbModels = _databaseService.GetPortfolios();
            _workspaces = new ObservableCollection<WorkspaceViewModel>();
            if (dbModels.Count == 0)
            {
                _workspaces.Add(new PortfolioViewModel());
            } 
            else
            {
                foreach (PortfolioModel pm in dbModels)
                {
                    _workspaces.Add(new PortfolioViewModel(pm));
                }
            }
            NewPortfolioCommand = new RelayCommand(param => this.CreateNewPortfolio());
            SavePortfoliosCommand = new RelayCommand(param => this.SavePortfolios());
        }

        public WorkspaceViewModel ActiveWorkspace
        {
            get
            {
                return _activeWorkspace;
            }
            set
            {
                _activeWorkspace = value;
                OnPropertyChanged("ActiveWorkspace");
            }
        }

        public ObservableCollection<WorkspaceViewModel> Workspaces
        {
            get
            {
                if (_workspaces == null)
                {
                    _workspaces = new ObservableCollection<WorkspaceViewModel>();
                    _workspaces.CollectionChanged += this.OnWorkspacesChanged;
                }
                return _workspaces;
            }
        }

        void OnWorkspacesChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null && e.NewItems.Count != 0)
            {
                foreach (WorkspaceViewModel workspace in e.NewItems)
                {
                    workspace.RequestClose += this.OnWorkspaceRequestClose;
                }
            }
            if (e.OldItems != null && e.OldItems.Count != 0)
            {
                foreach (WorkspaceViewModel workspace in e.OldItems)
                {
                    workspace.RequestClose -= this.OnWorkspaceRequestClose;
                }
            }
        }

        void OnWorkspaceRequestClose(object sender, EventArgs e)
        {
            WorkspaceViewModel workspace = sender as WorkspaceViewModel;
            workspace.Dispose();
            this.Workspaces.Remove(workspace);
        }

        public RelayCommand NewPortfolioCommand { get; set; }

        void CreateNewPortfolio()
        {
            PortfolioViewModel pvm = new PortfolioViewModel();
            _workspaces.Add(pvm);
            SetActiveWorkspace(pvm);
        }

        void SetActiveWorkspace(WorkspaceViewModel workspace)
        {
            ActiveWorkspace = workspace;
        }

        public RelayCommand SavePortfoliosCommand { get; set; }

        void SavePortfolios()
        {
            _databaseService.SavePortfolios(Workspaces);
        }
    }
}
