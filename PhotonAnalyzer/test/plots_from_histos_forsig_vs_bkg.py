############################################################################
## Date 6 Oct 2020
## Made by Arnab Purohit, Saha Institute of Nuclear Physics, Kolkata, India
############################################################################

from ROOT import TFile, TH1F, TH1D, kRed, kBlue, kGreen, TCanvas, gStyle, TLegend

gStyle.SetOptStat(0)
f2018 = TFile.Open("Outputfile_histograms_GJetMC2018_newThr_sig.root")
f2021 = TFile.Open("Outputfile_histograms_GJetMC2021_newThr_sig.root")
f2023 = TFile.Open("Outputfile_histograms_GJetMC2023_newThr_sig.root")
#f2024 = TFile.Open("Outputfile_histograms_DYMC2024_30Jan.root")

f2018_bkg = TFile.Open("Outputfile_histograms_GJetMC2018_newThr_bkg.root")
f2021_bkg = TFile.Open("Outputfile_histograms_GJetMC2021_newThr_bkg.root")
f2023_bkg = TFile.Open("Outputfile_histograms_GJetMC2023_newThr_bkg.root")
#f2024_bkg = TFile.Open("Outputfile_histograms_QCDMC2024_30Jan.root")
#f.ls()
canvas = TCanvas('canvas', '', 500, 500)
#hist = f.get_histogram('electron_momentum')
#histname = 'absCosThetaStar_CS'
histname1 = 'R9_EE'
histname2 = 'myR9_1_EE'
histname3 = 'myR9_2_EE'
histname4 = 'myR9_3_EE'
histname5 = 'nonFull5x5R9_EB'
absCosThetaStar_CS_1 = f2018.Get(histname1)
absCosThetaStar_CS_2 = f2018.Get(histname2)
absCosThetaStar_CS_3 = f2018.Get(histname3)
absCosThetaStar_CS_4 = f2018.Get(histname4)
absCosThetaStar_CS_5 = f2018.Get(histname5)


absCosThetaStar_CS_1_bkg = f2018_bkg.Get(histname1)
absCosThetaStar_CS_2_bkg = f2018_bkg.Get(histname2)
absCosThetaStar_CS_3_bkg = f2018_bkg.Get(histname3)
absCosThetaStar_CS_4_bkg = f2018_bkg.Get(histname4)
absCosThetaStar_CS_5_bkg = f2018_bkg.Get(histname5)


#legend = TLegend(0.15,0.55,0.4,0.85,"","brNDC")
legend = TLegend(0.55,0.55,0.8,0.85,"","brNDC")

legend.AddEntry(absCosThetaStar_CS_1,"CMSSW R_{9} Sig","pl")
legend.AddEntry(absCosThetaStar_CS_1_bkg,"CMSSW R_{9} Bkg","pl")
#legend.AddEntry(absCosThetaStar_CS_3,"R_{9} ver-2","pl")
#legend.AddEntry(absCosThetaStar_CS_2,"R_{9} ver-1","pl")
#legend.AddEntry(absCosThetaStar_CS_2_bkg,"R_{9} ver-1","pl")
#legend.AddEntry(absCosThetaStar_CS_3,"R_{9} ver-2","pl")
#legend.AddEntry(absCosThetaStar_CS_3_bkg,"R_{9} ver-2","pl")
#legend.AddEntry(absCosThetaStar_CS_4,"R_{9} ver-3","pl")
#legend.AddEntry(absCosThetaStar_CS_4_bkg,"R_{9} ver-3","pl")


absCosThetaStar_CS_1.SetTitle("")
absCosThetaStar_CS_1.GetYaxis().SetTitleOffset(1.5)
absCosThetaStar_CS_1.GetYaxis().SetTitleSize(0.03)
absCosThetaStar_CS_1.GetYaxis().SetLabelSize(0.02)
absCosThetaStar_CS_1.GetXaxis().SetTitleOffset(1.5)
absCosThetaStar_CS_1.GetXaxis().SetTitleSize(0.03)
absCosThetaStar_CS_1.GetXaxis().SetLabelSize(0.02)




absCosThetaStar_CS_1.GetXaxis().SetTitle("R_{9} in EE")
absCosThetaStar_CS_1.GetYaxis().SetTitle("Events/Bin width")



absCosThetaStar_CS_1.Scale(1/absCosThetaStar_CS_1.Integral())
absCosThetaStar_CS_2.Scale(1/absCosThetaStar_CS_2.Integral())
absCosThetaStar_CS_3.Scale(1/absCosThetaStar_CS_3.Integral())
absCosThetaStar_CS_4.Scale(1/absCosThetaStar_CS_4.Integral())
absCosThetaStar_CS_5.Scale(1/absCosThetaStar_CS_5.Integral())

absCosThetaStar_CS_1_bkg.Scale(1/absCosThetaStar_CS_1_bkg.Integral())
absCosThetaStar_CS_2_bkg.Scale(1/absCosThetaStar_CS_2_bkg.Integral())
absCosThetaStar_CS_3_bkg.Scale(1/absCosThetaStar_CS_3_bkg.Integral())
absCosThetaStar_CS_4_bkg.Scale(1/absCosThetaStar_CS_4_bkg.Integral())
absCosThetaStar_CS_5_bkg.Scale(1/absCosThetaStar_CS_5_bkg.Integral())



absCosThetaStar_CS_1.SetLineWidth(2)
absCosThetaStar_CS_2.SetLineWidth(2)
absCosThetaStar_CS_3.SetLineWidth(2)
absCosThetaStar_CS_4.SetLineWidth(2)
absCosThetaStar_CS_5.SetLineWidth(2)

absCosThetaStar_CS_1_bkg.SetMarkerSize(2)
absCosThetaStar_CS_2_bkg.SetMarkerSize(2)
absCosThetaStar_CS_3_bkg.SetMarkerSize(2)
absCosThetaStar_CS_4_bkg.SetMarkerSize(2)
absCosThetaStar_CS_5_bkg.SetMarkerSize(2)


"""
absCosThetaStar_CS_1.GetXaxis().SetRangeUser(0,1.2)
absCosThetaStar_CS_2.GetXaxis().SetRangeUser(0,1.2)
absCosThetaStar_CS_3.GetXaxis().SetRangeUser(0,1.2)

"""
absCosThetaStar_CS_1.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_2.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_3.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_4.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_5.GetXaxis().SetRangeUser(0,2)



absCosThetaStar_CS_1.SetLineColor(kBlue)
absCosThetaStar_CS_2.SetLineColor(kBlue)
absCosThetaStar_CS_3.SetLineColor(kBlue)
absCosThetaStar_CS_4.SetLineColor(kBlue)
absCosThetaStar_CS_5.SetLineColor(kBlue)


#absCosThetaStar_CS_1.SetLineStyle(1)
#absCosThetaStar_CS_2.SetLineStyle(2)
#absCosThetaStar_CS_3.SetLineStyle(3)



absCosThetaStar_CS_1_bkg.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_2_bkg.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_3_bkg.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_4_bkg.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_5_bkg.GetXaxis().SetRangeUser(0,2)



absCosThetaStar_CS_1_bkg.SetLineColor(kRed)
absCosThetaStar_CS_2_bkg.SetLineColor(kRed)
absCosThetaStar_CS_3_bkg.SetLineColor(kRed)
absCosThetaStar_CS_4_bkg.SetLineColor(kRed)
absCosThetaStar_CS_5_bkg.SetLineColor(kRed)


#absCosThetaStar_CS_1_bkg.SetLineStyle(1)
#absCosThetaStar_CS_2_bkg.SetLineStyle(2)
#absCosThetaStar_CS_3_bkg.SetLineStyle(3)


canvas.SetLogy()
#absCosThetaStar_CS_1.SetFillColor(kRed)
#absCosThetaStar_CS_1.SetLineColor(kRed)
absCosThetaStar_CS_1.Draw("HIST")
absCosThetaStar_CS_1_bkg.Draw("HIST SAME")
#absCosThetaStar_CS_3.Draw("HIST SAME")
#absCosThetaStar_CS_2.Draw("HIST")
#absCosThetaStar_CS_2_bkg.Draw("HIST SAME")
#absCosThetaStar_CS_3.Draw("HIST")
#absCosThetaStar_CS_3_bkg.Draw("HIST SAME")
#absCosThetaStar_CS_4.Draw("HIST")
#absCosThetaStar_CS_4_bkg.Draw("HIST SAME")
#absCosThetaStar_CS_5.Draw("HIST")
#absCosThetaStar_CS_5_bkg.Draw("HIST SAME")

legend.Draw("same")

#canvas.SaveAs(histname+'logy_allyears.png')
#canvas.SaveAs('alldef_R9inEE.png')
canvas.SaveAs('SigvsBkg_CMSSWR9_logy_R9inEE.png')
#canvas.SaveAs('SigvsBkg_CMSSWR9_R9inEE.png')
#canvas.SaveAs('SigvsBkg_ver1R9_R9inEE.png')
#canvas.SaveAs('SigvsBkg_ver2R9_R9inEE.png')
#canvas.SaveAs('SigvsBkg_ver3R9_R9inEE.png')
#canvas.SaveAs('SigvsBkg_ver2R9_logy_R9inEE.png')
#canvas.SaveAs('SigvsBkg_ver3R9_logy_R9inEE.png')
#canvas.SaveAs('SigvsBkg_ver1R9_logy_R9inEE.png')
