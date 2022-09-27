import numpy as np
import awkward as ak
import math as m
import matplotlib.pyplot as plt
import matplotlib as mpl
import mplhep as hep
import boost_histogram as bh

class yty_histplot:
    
    def __init__(self, hist_name, _type, bins_set=np.linspace(0,1,10+1),Figsize=(10,10)):
        self.name = hist_name
        self.__type = _type
        self.__bins_set = bh.axis.Variable(bins_set)
        self.__bins_array = ak.Array(bins_set)
        self.__auto_ylim_weight = 2
        mpl.style.use(hep.style.CMS)
        self.__Lumi=None 
        self.__Year=None 
        self.__xlabel='' 
        self.__y1label='' 
        self.__y2label=''
        self.__title=''
        self.__default_color_num = 0
        self.__draw_title=False
        self.__ylog=False
        self.__legend=False
        self.__legendx=0.85
        self.__legendy=0.85
        self.__legendloc=1
        self.__legendncol=1
        self.__legendcolumnspacing=None
        self.__legendlabelspacing=None
        self.__legendfontsize=None
        self.__figsize = Figsize
        
        if self.__type == 1:
            self.__fig, self.__ax = plt.subplots(figsize=self.__figsize)
            self.__ax.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
        elif self.__type == 2:
            f = plt.figure(figsize=self.__figsize,constrained_layout=False)
            gs = f.add_gridspec(nrows=5, ncols=3, hspace=0.05)
            ax1 = f.add_subplot(gs[:-1, :])
            ax2 = f.add_subplot(gs[-1, :])
            ax2.tick_params(axis='y',labelsize=15)
            self.__fig = f
            self.__ax1 = ax1
            self.__ax2 = ax2
            self.__ax1.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_ylim([0.5,1.5])
        else:
            print("You choose an illegal histtype, please redefine the histogram.")
            
        self.values_dict = {}
        self.weights_dict = {}
        self.hists_dict = {}
        self.stack_dict = {}
        self.__drawed_history = []
        print("Create type %d hist_plot named \"%s\"."%(_type, hist_name))
        
        
    def get_type(self):
        return self.__type
    
    
    def get_fig(self):
        if self.__type == 1 or self.__type == 2:
            return self.__fig
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
    
    
    def get_axes(self):
        if self.__type == 1:
            return self.__ax
        elif self.__type == 2:
            return [self.__ax1, self.__ax2]
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
        
        
    def get_bins(self):
        return self.__bins_set
    
    
    def get_history(self):
        return self.__drawed_history
        
        
    def append_values(self, label, v_akarray):
        try:
            assert type(label) == str
        except:
            print("Label must be string! Maybe you missed the label parameter.")
            return -1
        
        values = ak.concatenate(v_akarray)
#         print(values, len(values))
        self.values_dict[label] = values
        return self.values_dict
        
        
    def append_weights(self, label, w_akarray):
        try:
            assert type(label) == str
        except:
            print("Label must be string! Maybe you missed the label parameter.")
            return -1
        
        weights = ak.concatenate(w_akarray)
#         print(weights, len(weights))
        self.weights_dict[label] = weights
        return self.weights_dict
        
    
    def append_hist(self, label, hist):
        try:
            assert type(label) == str
        except:
            print("Label must be string! Maybe you missed the label parameter.")
            return -1
        
        self.hists_dict[label] = hist
        return self.hists_dict
        
    
    def set_log(self):
        if self.__type == 1:
            self.__ax.set_yscale('log')
            self.__ylog=True
        elif self.__type == 2:
            self.__ax1.set_yscale('log')
            self.__ylog=True
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
        
        
    def set_bins(self, bins_set):
        self.__bins_set = bh.axis.Variable(bins_set)
        self.__bins_array = ak.Array(bins_set)
        self.__fig.clf()
        if self.__type == 1:
            self.__fig, self.__ax = plt.subplots(figsize=self.__figsize)
            self.__ax.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
        elif self.__type == 2:
            f = plt.figure(figsize=self.__figsize,constrained_layout=False)
            gs = f.add_gridspec(nrows=5, ncols=3, hspace=0.05)
            ax1 = f.add_subplot(gs[:-1, :])
            ax2 = f.add_subplot(gs[-1, :])
            ax2.tick_params(axis='y',labelsize=15)
            self.__fig = f
            self.__ax1 = ax1
            self.__ax2 = ax2
            self.__ax1.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_ylim([0.5,1.5])
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
        if self.__draw_title==True:
            self.draw_title()
        self.hists_dict.clear()
        self.stack_dict.clear()
        self.__drawed_history = []
        print("Renew the hist & clear the hists_dict.")
        return self.__bins_set
        
        
    def set_title(self, Lumi=None, Year=None, xlabel='', y1label='', y2label='', title='',cmstitle=False):
        self.__Lumi = Lumi
        self.__Year = Year
        self.__xlabel = xlabel 
        self.__y1label = y1label 
        self.__y2label = y2label
        self.__title = title
        self.draw_title(cmstitle)
        return self.__fig
    
    
    def set_autoylim(self, ylim):
        self.__auto_ylim_weight = ylim
        return self.__auto_ylim_weight    
    
    def set_grid(self, gridtype):
        if self.__type == 1:
            self.__ax.grid(gridtype)
        elif self.__type == 2:
            self.__ax1.grid(gridtype)
            self.__ax2.grid(gridtype)
        return self.__fig
    
    def set_legend(self, legendbool=True, x=0.85, y=0.85, loc=1, ncol=1, columnspacing=None, labelspacing=None, fontsize=None):
#         self.__fig.legend()
        self.__legend=legendbool
        self.__legendx=x
        self.__legendy=y
        self.__legendloc=loc
        self.__legendncol=ncol
        self.__legendcolumnspacing=columnspacing
        self.__legendlabelspacing=labelspacing
        self.__legendfontsize=fontsize
#         print('test1 ncol=%d'%self.__legendncol)
        return self.__legend
    
    def draw_title(self,cmstitle=False):
        if self.__type == 1:
            if cmstitle:
                hep.cms.label(ax=self.__ax,year=self.__Year,lumi=self.__Lumi)
            self.__ax.set_ylabel(self.__y1label)
            self.__ax.set_xlabel(self.__xlabel)
            self.__ax.set_title(self.__title)
        elif self.__type == 2:
            if cmstitle:
                hep.cms.label(ax=self.__ax1,year=self.__Year,lumi=self.__Lumi)
            self.__ax1.set_ylabel(self.__y1label)
            self.__ax2.set_ylabel(self.__y2label)
            self.__ax2.set_xlabel(self.__xlabel)
            self.__ax1.set_title(self.__title)
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
        self.__draw_title=True
        return self.__fig
    
    def add_text(self, x, y, content, size, ax_id=1):
        if self.__type == 1:
            self.__ax.text(x, y, content, fontsize=size, transform=self.__ax.transAxes)
        elif self.__type == 2:
            if ax_id==1:
                self.__ax1.text(x, y, content, fontsize=size, transform=self.__ax1.transAxes)
            elif ax_id==2:
                self.__ax2.text(x, y, content, fontsize=size, transform=self.__ax2.transAxes)
            else:
                print("Wrong ax_id! please set it to 1 or 2.")
                return -1
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
        return self.__fig
    
    def add_two_hist(self, label1, label2, stack=False):
        if stack==False:
            try:
                hist1 = self.hists_dict[label1]
            except:
                values1 = self.values_dict[label1]
                try:
                    w_list1 = self.weights_dict[label1]
                except:
                    w_list1 = 1
                hist1 = bh.Histogram(self.__bins_set, storage=bh.storage.Weight())
                hist1.fill(values1, weight=w_list1)
            try:
                content1, weighted_yerr1 = hist1.view().value, np.sqrt(hist1.view().variance)
            except:
                [content1, weighted_yerr1] = hist1
        else:
            [content1, weighted_yerr1] = self.stack_dict[label1]
        try:
            hist2 = self.hists_dict[label2]
        except:
            values2 = self.values_dict[label2]
            try:
                w_list2 = self.weights_dict[label2]
            except:
                w_list2 = 1
            hist2 = bh.Histogram(self.__bins_set, storage=bh.storage.Weight())
            hist2.fill(values2, weight=w_list2)
        try:
            content2, weighted_yerr2 = hist2.view().value, np.sqrt(hist2.view().variance)
        except:
            [content2, weighted_yerr2] = hist2
        content, weighted_yerr = content1 + content2, np.sqrt(weighted_yerr1**2 + weighted_yerr2**2)
        return content, weighted_yerr
    
    
    def get_max_bin(self, label_list, stack=True):
        bhv = self.__bins_set
        widths = np.array(bhv)[:,1]-np.array(bhv)[:,0]
        max_bin = 0
        if stack==True:
            for label in label_list:
#                 print(label)
#                 print(max_bin)
                try:
                    content = self.stack_dict[label][0]
                except:
                    continue
                max_bin = max_bin if max_bin>np.max(content/widths) else np.max(content/widths)
        else:
            for label in label_list:
                try:
                    content = self.hists_dict[label].view().value
                except:
                    try:
                        content = self.hists_dict[label][0]
                    except:
                        continue
                max_bin = max_bin if max_bin>np.max(content/widths) else np.max(content/widths)
        
        return max_bin
    
    
    def draw(self, label_list="all", stack=False, histtype_list=["step"], yerr_tf_list=[False], color_list=[None], save=None, clear=False):
        if clear==True:
            self.__fig.clf()
            self.__default_color_num = 0
            if self.__type == 1:
                self.__fig, self.__ax = plt.subplots(figsize=self.__figsize)
                self.__ax.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            elif self.__type == 2:
                f = plt.figure(figsize=self.__figsize,constrained_layout=False)
                gs = f.add_gridspec(nrows=5, ncols=3, hspace=0.05)
                ax1 = f.add_subplot(gs[:-1, :])
                ax2 = f.add_subplot(gs[-1, :])
                ax2.tick_params(axis='y',labelsize=15)
                self.__fig = f
                self.__ax1 = ax1
                self.__ax2 = ax2
                self.__ax1.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
                self.__ax2.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
                self.__ax2.set_ylim([0.5,1.5])
            if self.__draw_title==True:
                self.draw_title()
            if self.__ylog==True:
                if self.__type == 1:
                    self.__ax.set_yscale('log')
                    self.__ylog=True
                elif self.__type == 2:
                    self.__ax1.set_yscale('log')
                    self.__ylog=True
            self.hists_dict.clear()
            self.stack_dict.clear()
            self.__drawed_history = []
        else:
            self.__fig.legends = []
        
        if self.__type == 1:
            ax = self.__ax
        elif self.__type == 2:
            ax = self.__ax1
        else:
            print("Wrong plot_type! Please redefine the histplot.")
            return -1
        
        if label_list=="all":
            labels = list(self.values_dict.keys())
        else:
            labels = label_list
            if type(labels)==str:
                labels = [labels]
        for label in labels:
            try:
                values = self.values_dict[label]
            except:
                print("Histplot:%s\tNo label named \"%s\""%(self.name, label))
                continue
            hist = bh.Histogram(self.__bins_set, storage=bh.storage.Weight())
            try:
                w_list = self.weights_dict[label]
            except:
                print("Histplot:%s\tNo weights saved in label \"%s\", use w=1 instead."%(self.name, label))
                w_list = 1
            hist.fill(values, weight=w_list)
            self.hists_dict[label] = hist
#                 content, weighted_yerr = hist.view().value, np.sqrt(hist.view().variance)
        
        if stack==False:
            for n_l, label in enumerate(labels):
                if label in self.hists_dict.keys():
                    try:
                        yerr_tf = yerr_tf_list[n_l]
                    except:
                        yerr_tf = False
                    try:
                        histtype = histtype_list[n_l]
                    except:
                        histtype = "step"
                    try:
                        color = color_list[n_l]
                    except:
                        color = None
                    try:
                        hist_draw = self.hists_dict[label]
                        content, weighted_yerr = hist_draw.view().value, np.sqrt(hist_draw.view().variance)
                    except:
                        [content, weighted_yerr] = self.hists_dict[label]
                    if histtype == "errorbar":
                        yerr_tf = True
                    if color == None:
                        color = plt.rcParams['axes.prop_cycle'].by_key()['color'][self.__default_color_num%10]
                        self.__default_color_num += 1
                    if yerr_tf:
                        hep.histplot(content, bins=self.__bins_array, yerr=weighted_yerr, binwnorm=1, ax=ax, label=label, histtype=histtype, color=color)
                        print("draw ",label)
                    else:
                        hep.histplot(content, bins=self.__bins_array, yerr=None, binwnorm=1, ax=ax, label=label, histtype=histtype, color=color)
                        print("draw ",label)
                    history_info = [label,"hist",histtype,str(yerr_tf*1),str(color)]
                    self.__drawed_history.append(history_info)
            max_bin = self.get_max_bin(labels, stack=False)        
        else:
            self.stack_dict.clear()
            for n_l, label in enumerate(labels):
                if label in self.hists_dict.keys():
                    try:
                        assert n_l>0
                        label1 = labels[n_l-1]
                        label2 = labels[n_l]
                    except:
                        try:
                            hist = self.hists_dict[label]
                            stack_content, stack_weighted_yerr = hist.view().value, np.sqrt(hist.view().variance)
                        except:
                            [stack_content, stack_weighted_yerr] = self.hists_dict[label]
                        self.stack_dict[label] = [stack_content, stack_weighted_yerr]
                        continue
                    stack_content, stack_weighted_yerr = self.add_two_hist(label1, label2, stack=True)
                    self.stack_dict[label2] = [stack_content, stack_weighted_yerr]
                    
            try:        
                labels.reverse()
            except:
                return self.__fig
            try:
                yerr_tf_list.reverse()
            except:
                yerr_tf_list = [False]
            try:
                histtype_list.reverse()
            except:
                histtype_list = ["step"]
            try:
                color_list.reverse()
            except:
                color = [None]
                
            for n_lr, label in enumerate(labels):
                if label in self.hists_dict.keys():
                    try:
                        yerr_tf = yerr_tf_list[n_lr]
                    except:
                        yerr_tf = False
                    try:
                        histtype = histtype_list[n_lr]
                    except:
                        histtype = "step"
                    try:
                        color = color_list[n_lr]
                    except:
                        color = None
                    hist_draw = self.hists_dict[label]
                    [content, weighted_yerr] = self.stack_dict[label]
                    if histtype == "errorbar":
                        yerr_tf = True
                    if color == None:
                        color = plt.rcParams['axes.prop_cycle'].by_key()['color'][self.__default_color_num%10]
                        self.__default_color_num += 1
                    if yerr_tf:
                        hep.histplot(content, bins=self.__bins_array, yerr=weighted_yerr, binwnorm=1, ax=ax, label=label, histtype=histtype, color=color)
                        print("draw ",label)
                    else:
                        hep.histplot(content, bins=self.__bins_array, yerr=None, binwnorm=1, ax=ax, label=label, histtype=histtype, color=color)
                        print("draw ",label)
                    history_info = [label,"stack",histtype,str(yerr_tf*1),str(color)]
                    self.__drawed_history.append(history_info)    
            max_bin = self.get_max_bin(labels, stack=True)
                        
        #Further adjustment(make plot more beautiful)
        if self.__type == 1:
            self.__ax.set_ylim([0,self.__auto_ylim_weight*max_bin])
            yticks1 = self.__ax.yaxis.get_major_ticks()
            yticks1[0].label1.set_visible(False)
            #yticks1[-1].label1.set_visible(False)
        elif self.__type == 2:
            self.__ax1.set_ylim([0,self.__auto_ylim_weight*max_bin])
            yticks1 = self.__ax1.yaxis.get_major_ticks()
            yticks1[0].label1.set_visible(False)
            #yticks1[-1].label1.set_visible(False)

            yticks2 = self.__ax2.yaxis.get_major_ticks()
            yticks2[0].label1.set_visible(False)

            xticks1 = self.__ax1.xaxis.get_major_ticks()
            for xtick in xticks1:
                xtick.label1.set_visible(False)
            self.__ax2.plot([self.__bins_set[0][0],self.__bins_set[-1][-1]],[1,1],'k--')
            
        if self.__legend==True:
#             print('test: ncol=%d'%self.__legendncol)
            self.__fig.legend(bbox_to_anchor=(self.__legendx, self.__legendy), loc=self.__legendloc, ncol=self.__legendncol, borderaxespad=0, columnspacing=self.__legendcolumnspacing, labelspacing=self.__legendlabelspacing, fontsize=self.__legendfontsize)
        if save!=None:
            self.__fig.savefig(str(save)+'.png') 
        return self.__fig
    
    def merge(self,plus_labels,minus_labels,output_label):
        for plus_label in plus_labels:
            if not plus_label in self.values_dict.keys():
                print('No label named %s, it\'s in plus_labels.'%plus_label)
                return -1
        for minus_label in minus_labels:
            if not minus_label in self.values_dict.keys():
                print('No label named %s, it\'s in minus_labels.'%minus_label)
                return -1
        output_content = 0
        output_error = 0
        for label1 in plus_labels:
            try:
                hist1 = self.hists_dict[label1]
            except:
                values1 = self.values_dict[label1]
                try:
                    w_list1 = self.weights_dict[label1]
                except:
                    w_list1 = 1
                hist1 = bh.Histogram(self.__bins_set, storage=bh.storage.Weight())
                hist1.fill(values1, weight=w_list1)
            content1, weighted_yerr1 = hist1.view().value, np.sqrt(hist1.view().variance)
            output_content += content1
            output_error = np.sqrt(output_error**2+weighted_yerr1**2)
        for label2 in minus_labels:
            try:
                hist2 = self.hists_dict[label2]
            except:
                values2 = self.values_dict[label2]
                try:
                    w_list2 = self.weights_dict[label2]
                except:
                    w_list2 = 1
                hist2 = bh.Histogram(self.__bins_set, storage=bh.storage.Weight())
                hist2.fill(values2, weight=w_list2)
            content2, weighted_yerr2 = hist2.view().value, np.sqrt(hist2.view().variance)
            output_content -= content2
            output_error = np.sqrt(output_error**2+weighted_yerr2**2)
        self.hists_dict[output_label] = [output_content, output_error]
        return self.__fig
    
    #return the ratio of label1/label2
    def compare(self, label1, label2, stack1=False, stack2=False, Color='black', clear=True, ylim=[0.5,1.5]):
        if self.__type == 1:
            self.convert_type(1, 2)
        elif self.__type == 2:
            if clear==True:
                self.__ax2.cla()
            self.__ax2.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_ylim(ylim)
            self.__ax2.grid("--")
            yticks2 = self.__ax2.yaxis.get_major_ticks()
            yticks2[0].label1.set_visible(False)
            if clear==True:
                self.__ax2.plot([self.__bins_set[0][0],self.__bins_set[-1][-1]],[1,1],'k--')
            if self.__draw_title==True:
                self.__ax2.set_ylabel(self.__y2label, size=20)
                self.__ax2.set_xlabel(self.__xlabel)
        else:
            print("Wrong plot_type!")
            return -1
        ax = self.__ax2
        if stack1 == True:
            [content1, weight_yerr1] = self.stack_dict[label1]
        else:
            content1, weight_yerr1 = self.hists_dict[label1].view().value, np.sqrt(self.hists_dict[label1].view().variance)
        if stack2 == True:
            [content2, weight_yerr2] = self.stack_dict[label2]
        else:
            content2, weight_yerr2 = self.hists_dict[label2].view().value, np.sqrt(self.hists_dict[label2].view().variance)
        ratio_content = content1/content2
        ratio_yerr = weight_yerr1/content2
#         print(content1, weight_yerr1)
#         print(content2)
#         print(ratio_content,ratio_yerr)
        hep.histplot(ratio_content, bins=self.hists_dict[label1].axes[0].edges, yerr=ratio_yerr, ax=ax, histtype="errorbar", color=Color)
        
        return self.__fig
        
        
    def convert_type(self, type_before, type_after):
        if type_before==1 and type_after==2:
            self.__type = type_after
            self.__fig.clf()
            f = plt.figure(figsize=self.__figsize,constrained_layout=False)
            gs = f.add_gridspec(nrows=5, ncols=3, hspace=0.05)
            ax1 = f.add_subplot(gs[:-1, :])
            ax2 = f.add_subplot(gs[-1, :])
            ax2.tick_params(axis='y',labelsize=15)
            self.__fig = f
            self.__ax1 = ax1
            self.__ax2 = ax2
            self.__ax1.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
            self.__ax2.set_ylim([0.5,1.5])
        elif type_before==2 and type_after==1:
            self.__type = type_after
            self.__fig.clf()
            self.__fig, self.__ax = plt.subplots(figsize=self.__figsize)
            self.__ax.set_xlim([self.__bins_set[0][0],self.__bins_set[-1][-1]])
        else:
            print("Illegal histtype! Nothing will be changed.")
            return -1
        if self.__draw_title==True:
            self.draw_title()
        if self.__type == 1:
            ax = self.__ax
        elif self.__type == 2:
            ax = self.__ax1
        label_stack = []
        label_hist = []
        for label_record in self.__drawed_history:
#             print(label_record)
            [label,plot_type,histtype,yerr_tf,color] = label_record
            yerr_tf = bool(int(yerr_tf))
            hist_draw = self.hists_dict[label]
            if histtype == "errorbar":
                yerr_tf = True
#             if color == 'None':
#                 color = None
            if plot_type=="hist":
                content, weighted_yerr = hist_draw.view().value, np.sqrt(hist_draw.view().variance)
                label_hist.append(label)
            elif plot_type=="stack":
                [content, weighted_yerr] = self.stack_dict[label]
                label_stack.append(label)
            else:
                print("Something unexpected happened, please contact yty at once :(")
                return -1
            if yerr_tf:
                hep.histplot(content, bins=self.__bins_array, yerr=weighted_yerr, binwnorm=1, ax=ax, label=label, histtype=histtype, color=color)
            else:
                hep.histplot(content, bins=self.__bins_array, yerr=None, binwnorm=1, ax=ax, label=label, histtype=histtype, color=color)
        max_bin = np.max([self.get_max_bin(label_stack, stack=True),self.get_max_bin(label_hist, stack=False)])
        
        if self.__type == 1:
            self.__ax.set_ylim([0,self.__auto_ylim_weight*max_bin])
            yticks1 = self.__ax.yaxis.get_major_ticks()
            yticks1[0].label1.set_visible(False)
            #yticks1[-1].label1.set_visible(False)
        elif self.__type == 2:
            self.__ax1.set_ylim([0,self.__auto_ylim_weight*max_bin])
            yticks1 = self.__ax1.yaxis.get_major_ticks()
            yticks1[0].label1.set_visible(False)
            #yticks1[-1].label1.set_visible(False)

            yticks2 = self.__ax2.yaxis.get_major_ticks()
            yticks2[0].label1.set_visible(False)

            xticks1 = self.__ax1.xaxis.get_major_ticks()
            for xtick in xticks1:
                xtick.label1.set_visible(False)
            self.__ax2.plot([self.__bins_set[0][0],self.__bins_set[-1][-1]],[1,1],'k--')
        if self.__legend==True:
            self.__fig.legend(bbox_to_anchor=(self.__legendx, self.__legendy), loc=self.__legendloc, ncol=self.__legendncol, borderaxespad=0, columnspacing=self.__legendcolumnspacing, labelspacing=self.__legendlabelspacing, fontsize=self.__legendfontsize)
        return self.__fig

    
    def draw_uncertainty(self,label,stack=True,name='unc.',export=False,ex_content=None, ex_weight_yerr=None):
        if export==False:
            try:
                if stack==True:
                    [content, weight_yerr] = self.stack_dict[label]
                else:
                    try:
                        
                        content, weight_yerr = self.hists_dict[label].view().value, np.sqrt(self.hists_dict[label].view().variance)
                    except:
                        [content, weighted_yerr] = self.hists_dict[label]
            except:
                print("Cannot draw uncertainty based on label named %s, please check."%label)
                return -1
        else:
            content = ex_content
            weight_yerr = ex_weight_yerr
        if self.__type==1:
            ax = self.__ax
            x_list = []
            yupper_list = []
            ylower_list = []
            for n,x_range in enumerate(self.__bins_set):
                yupper = content[n]+weight_yerr[n]
                ylower = content[n]-weight_yerr[n]
                x_list.append(x_range[0])
                x_list.append(x_range[1])
                yupper_list.append(yupper)
                yupper_list.append(yupper)
                ylower_list.append(ylower)
                ylower_list.append(ylower)
            ax.fill_between(x_list, 
                            ylower_list, 
                            yupper_list,
                            facecolor='white',
                            alpha=0,label=name, zorder=2.5, hatch="//")
        elif self.__type==2:
            ratio_unce = weight_yerr/content
            ax1 = self.__ax1
            ax2 = self.__ax2
            x_list = []
            yupper_list = []
            ylower_list = []
            rupper_list = []
            rlower_list = []
            for n,x_range in enumerate(self.__bins_set):
                yupper = content[n]+weight_yerr[n]
                ylower = content[n]-weight_yerr[n]
                rupper = ratio_unce[n]
                rlower = -ratio_unce[n]

                x_list.append(x_range[0])
                x_list.append(x_range[1])
                yupper_list.append(yupper)
                yupper_list.append(yupper)
                ylower_list.append(ylower)
                ylower_list.append(ylower)

                rupper_list.append(1+rupper)
                rupper_list.append(1+rupper)
                rlower_list.append(1+rlower)
                rlower_list.append(1+rlower)

            ax1.fill_between(x_list, 
                            ylower_list, 
                            yupper_list,
                            facecolor='white',
                            alpha=0,label=name, zorder=2.5, hatch="//")
            ax2.fill_between(x_list, 
                            rlower_list, 
                            rupper_list,
                            facecolor='grey',
                            alpha=0.25,zorder=2.5, hatch="***",color="grey")

        else:
            print("Wrong plot_type!")
            return -1
        if self.__legend==True:
            self.__fig.legend(bbox_to_anchor=(self.__legendx, self.__legendy), loc=self.__legendloc, ncol=self.__legendncol, borderaxespad=0, columnspacing=self.__legendcolumnspacing, labelspacing=self.__legendlabelspacing, fontsize=self.__legendfontsize)
        return self.__fig
            
    
    def save(self,name='fig'):
        self.__fig.savefig(str(name))
        return self.__fig
            
            
            
            