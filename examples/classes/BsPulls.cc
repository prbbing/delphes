#include "BsPulls.h"

//
// Final state configuration description
//
// Constructor
BsPulls::BsPulls()
{
	//
	// Pulls
	// Ds vertex
	h_DsXv = new TH1D("h_DsXv","Ds X-vertex pull",100,-10.,10.);
	h_DsYv = new TH1D("h_DsYv","Ds Y-vertex pull",100,-10.,10.);
	h_DsZv = new TH1D("h_DsZv","Ds Z-vertex pull",100,-10.,10.);
	// Ds vertex momentum
	h_DsPx = new TH1D("h_DsPx","Ds X-momentum pull",100,-10.,10.);
	h_DsPy = new TH1D("h_DsPy","Ds Y-momentum pull",100,-10.,10.);
	h_DsPz = new TH1D("h_DsPz","Ds Z-momentum pull",100,-10.,10.);
	// Bs vertex
	h_BsXv = new TH1D("h_BsXv","Bs X-vertex pull",100,-10.,10.);
	h_BsYv = new TH1D("h_BsYv","Bs Y-vertex pull",100,-10.,10.);
	h_BsZv = new TH1D("h_BsZv","Bs Z-vertex pull",100,-10.,10.);
	// Bs vertex momentum
	h_BsPx = new TH1D("h_BsPx","Bs X-momentum pull",100,-10.,10.);
	h_BsPy = new TH1D("h_BsPy","Bs Y-momentum pull",100,-10.,10.);
	h_BsPz = new TH1D("h_BsPz","Bs Z-momentum pull",100,-10.,10.);

	//
	// Mass plots
	h_BsMass  = new TH1D("h_BsMass" , "Bs mass (GeV)" , 100, 5.2, 5.5);
	h_BsMpull = new TH1D("h_BsMpull", "Bs mass pull " , 100, -10., 10.);
	h_BsMerr  = new TH1D("h_BsMerr" , "Bs mass error ", 100, 0., 0.1);
}

//
// Destructor
BsPulls::~BsPulls() 
{
}

void BsPulls::Fill(VState* BsState, VertexMore* vDs, VertexMore* vBs)
{
	//
	// Bs Vertex
	GenParticle* pBsPi  = BsState ->GetGen(0);	// Pion from Bs
	TVector3 gvBs(pBsPi->X, pBsPi->Y, pBsPi->Z);	// Bs generated vertex
	TVectorD rvBs = vBs->GetXv();			// Bs reconstructed vertex
	TMatrixDSym cvBs = vBs->GetXvCov();		// Bs vertex covariance
	// Fill
	h_BsXv->Fill((rvBs(0)-gvBs(0))/TMath::Sqrt(cvBs(0,0)));
	h_BsYv->Fill((rvBs(1)-gvBs(1))/TMath::Sqrt(cvBs(1,1)));
	h_BsZv->Fill((rvBs(2)-gvBs(2))/TMath::Sqrt(cvBs(2,2)));
	// Bs Momentum
	GenParticle* pBs = BsState->GetMother();
	TVector3 gpBs(pBs->Px, pBs->Py, pBs->Pz);	// Bs generated momentum
	TVector3 rpBs = vBs->GetTotalP();		// Bs reconstructed momentum
	TMatrixDSym cpBs = vBs->GetTotalPcov();		// Bs momentum covariance
	// Fill
	h_BsPx->Fill((rpBs(0)-gpBs(0))/TMath::Sqrt(cpBs(0,0)));
	h_BsPy->Fill((rpBs(1)-gpBs(1))/TMath::Sqrt(cpBs(1,1)));
	h_BsPz->Fill((rpBs(2)-gpBs(2))/TMath::Sqrt(cpBs(2,2)));

	//
	// Ds Vertex
	VState* DsState  = BsState ->GetVState(0);	// Ds from Bs
	GenParticle* pDsPi  = DsState ->GetGen(0);	// Pion from Ds
	TVector3 gvDs(pDsPi->X, pDsPi->Y, pDsPi->Z);	// Ds generated vertex
	TVectorD rvDs = vDs->GetXv();			// Ds reconstructed vertex
	TMatrixDSym cvDs = vDs->GetXvCov();		// Ds vertex covariance
	// Fill
	h_DsXv->Fill((rvDs(0)-gvDs(0))/TMath::Sqrt(cvDs(0,0)));
	h_DsYv->Fill((rvDs(1)-gvDs(1))/TMath::Sqrt(cvDs(1,1)));
	h_DsZv->Fill((rvDs(2)-gvDs(2))/TMath::Sqrt(cvDs(2,2)));
	// Ds Momentum
	GenParticle* pDs = DsState->GetMother();
	TVector3 gpDs(pDs->Px, pDs->Py, pDs->Pz);	// Ds generated momentum
	TVector3 rpDs = vDs->GetTotalP();		// Ds reconstructed momentum
	TMatrixDSym cpDs = vDs->GetTotalPcov();		// Ds momentum covariance
	// Fill
	h_DsPx->Fill((rpDs(0)-gpDs(0))/TMath::Sqrt(cpDs(0,0)));
	h_DsPy->Fill((rpDs(1)-gpDs(1))/TMath::Sqrt(cpDs(1,1)));
	h_DsPz->Fill((rpDs(2)-gpDs(2))/TMath::Sqrt(cpDs(2,2)));
	
	//
	// Bs mass plots
	TVector3 rBsPi = vBs->GetMomentum(0);	// Momentum pion from Bs
	TVector3 rBsDs = vBs->GetMomentum(1);	// Momentum Ds from Bs
	Double_t PiMass = pBsPi->Mass;		// Pion mass
	Double_t DsMass = pDs->Mass;		// Ds mass
	Double_t BsMass = pBs->Mass;		// Bs mass
	Double_t Epi = TMath::Sqrt(PiMass*PiMass+rBsPi.Mag2());	// Energy pion from Bs
	Double_t Eds = TMath::Sqrt(DsMass*DsMass+rBsDs.Mag2());	// Energy Ds from Bs
	Double_t Etot = Epi + Eds;		// Bs energy
	TVector3 Ptot = rBsPi + rBsDs;		// Bs momentum
	Double_t rBsMass = TMath::Sqrt(Etot*Etot-Ptot.Mag2());	// Reconstructed Bs mass
	// Mass error
	TVector3 dm1 = (1./BsMass)*((Etot/Epi)*rBsPi-Ptot);	// dm/dp1
	TVector3 dm2 = (1./BsMass)*((Etot/Eds)*rBsDs-Ptot);	// dm/dp2
	Double_t dmp[6] = {dm1(0), dm1(1), dm1(2),dm2(0), dm2(1), dm2(2)};
	TVectorD DmDp(6, dmp);
	TMatrixDSym Bcov = vBs->GetBigCov();			
	TMatrixDSym pcov = Bcov.GetSub(3,8,3,8);		// cov(p1,p2)
	Double_t mBsErr = TMath::Sqrt(pcov.Similarity(DmDp));	// Error on Bs mass
	// Fill
	h_BsMass->Fill(rBsMass);
	h_BsMerr->Fill(mBsErr);
	h_BsMpull->Fill((rBsMass-BsMass)/mBsErr);
}

// Print 
void BsPulls::Print() 
{
	//
	// Ds plots
	TCanvas * cnv = new TCanvas("cnv","Ds vertex pulls",10,10, 900,600);
	cnv->Divide(3,2);
	// X
	cnv->cd(1); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_DsXv->Fit("gaus"); h_DsXv->Draw();
	// Y
	cnv->cd(2); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_DsYv->Fit("gaus"); h_DsYv->Draw();
	// Z
	cnv->cd(3); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_DsZv->Fit("gaus"); h_DsZv->Draw();
	// Px
	cnv->cd(4); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_DsPx->Fit("gaus"); h_DsPx->Draw();
	// Py
	cnv->cd(5); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_DsPy->Fit("gaus"); h_DsPy->Draw();
	// Pz
	cnv->cd(6); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_DsPz->Fit("gaus"); h_DsPz->Draw();

	//
	// Bs plots
	TCanvas * cnv1 = new TCanvas("cnv1","Bs vertex pulls",100,100, 900,600);
	cnv1->Divide(3,2);
	// X
	cnv1->cd(1); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsXv->Fit("gaus"); h_BsXv->Draw();
	// Y
	cnv1->cd(2); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsYv->Fit("gaus"); h_BsYv->Draw();
	// Z
	cnv1->cd(3); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsZv->Fit("gaus"); h_BsZv->Draw();
	// Px
	cnv1->cd(4); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsPx->Fit("gaus"); h_BsPx->Draw();
	// Py
	cnv1->cd(5); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsPy->Fit("gaus"); h_BsPy->Draw();
	// Pz
	cnv1->cd(6); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsPz->Fit("gaus"); h_BsPz->Draw();

	//
	// Bs mass plots
	TCanvas * cnv2 = new TCanvas("cnv2","Bs mass plots",200,200, 900,600);
	cnv2->Divide(2,2);
	cnv2->cd(1); 
	gStyle->SetOptStat(111111); 
	h_BsMass->Draw();
	cnv2->cd(2); 
	gStyle->SetOptStat(111111); 
	h_BsMerr->Draw();
	cnv2->cd(3); gPad->SetLogy(1);
	gStyle->SetOptStat(111111); gStyle->SetOptFit(1111);
	h_BsMpull->Fit("gaus"); h_BsMpull->Draw();

}
