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
#f.ls()
canvas = TCanvas('canvas', '', 500, 500)
#hist = f.get_histogram('electron_momentum')
#histname = 'absCosThetaStar_CS'
#histname = 'R9_EE'
#histname = 'nonFull5x5R9_EB'
histname = 'myR9_3_EE'
absCosThetaStar_CS_1 = f2018.Get(histname)
absCosThetaStar_CS_2 = f2021.Get(histname)
absCosThetaStar_CS_3 = f2023.Get(histname)
#absCosThetaStar_CS_4 = f2024.Get(histname)

legend = TLegend(0.15,0.55,0.4,0.85,"","brNDC")

legend.AddEntry(absCosThetaStar_CS_1,"2018","pl")
legend.AddEntry(absCosThetaStar_CS_2,"2021","pl")
legend.AddEntry(absCosThetaStar_CS_3,"2023","pl")
#legend.AddEntry(absCosThetaStar_CS_4,"2024","pl")

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
#absCosThetaStar_CS_4.Scale(1/absCosThetaStar_CS_4.Integral())

"""
absCosThetaStar_CS_1.SetLineWidth(2)
absCosThetaStar_CS_2.SetLineWidth(2)
absCosThetaStar_CS_3.SetLineWidth(2)
absCosThetaStar_CS_4.SetLineWidth(2)
"""

absCosThetaStar_CS_1.GetXaxis().SetRangeUser(0,1.2)
absCosThetaStar_CS_2.GetXaxis().SetRangeUser(0,1.2)
absCosThetaStar_CS_3.GetXaxis().SetRangeUser(0,1.2)
#absCosThetaStar_CS_4.GetXaxis().SetRangeUser(0,1.2)
"""
absCosThetaStar_CS_1.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_2.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_3.GetXaxis().SetRangeUser(0,2)
absCosThetaStar_CS_4.GetXaxis().SetRangeUser(0,2)
"""

absCosThetaStar_CS_1.SetLineColor(kBlue)
absCosThetaStar_CS_2.SetLineColor(kRed)
absCosThetaStar_CS_3.SetLineColor(kGreen)
#absCosThetaStar_CS_4.SetLineColor(6)

absCosThetaStar_CS_1.SetLineStyle(0)
absCosThetaStar_CS_2.SetLineStyle(1)
absCosThetaStar_CS_3.SetLineStyle(2)
#absCosThetaStar_CS_4.SetLineStyle(3)

canvas.SetLogy()
#absCosThetaStar_CS_1.SetFillColor(kRed)
#absCosThetaStar_CS_1.SetLineColor(kRed)
absCosThetaStar_CS_1.Draw("HIST")
absCosThetaStar_CS_2.Draw("HIST SAME")
absCosThetaStar_CS_3.Draw("HIST SAME")
#absCosThetaStar_CS_4.Draw("HIST SAME")
legend.Draw("same")

canvas.SaveAs(histname+'logy_allyears.png')
#canvas.SaveAs(histname+'_allyears.png')
