#include "Window.h"
#include "Scorpion.h"

using namespace System::Diagnostics;

namespace Scorpion
{
	void Window::refreshList()
	{
		// TODO: There has to be a better way of doing this
		if (procLV->Items->Count > 0)
		{
			procLV->Clear();
			dllView->Clear();
			procLV->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->chkBox, this->procNm,
					this->procThr, this->procPID, this->procPPID
			});
			dllView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->chkCol, this->dllPath });
		}

		// Let's create a system snapshot and a process entry object. 
		HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 pe32;

		// If our snapshot is invalid, we can't do anything.
		// TODO: try{} catch{}
		if (hProc == INVALID_HANDLE_VALUE)
			return; // Figure out what goes before return.

		// We have our snapshot, let's size PROCESSENTRY32
		pe32.dwSize = sizeof(PROCESSENTRY32);
		// Let's check and see if the snapshot has any processes
		if (Process32First(hProc, &pe32))
			// Walk processes, fill our view with process information (yum)!
			while (Process32Next(hProc, &pe32))
				procLV->Items->Add(gcnew ListViewItem(gcnew array<String^>
				{	"",
					gcnew String(pe32.szExeFile),
					pe32.cntThreads.ToString(),
					pe32.th32ProcessID.ToString(),
					pe32.th32ParentProcessID.ToString() } ));
		// Let's close our handle now, and get rid of it.
		CloseHandle(hProc);
	}

	System::Void Window::Window_Load(System::Object^  sender, System::EventArgs^  e) 
	{ 
		// First, let's refresh our list
		refreshList(); 

		// Afterwards, let's detect the OS for PROCESS_ALL_ACCESS permissions
		// It appears that >= Win Vista there are issues if non-privileged handles are used. 

		if ((DWORD)(LOBYTE(LOWORD(GetVersion())) >= 6)) procAAChk->Checked = true;
	}
	System::Void Window::procRefBt_Click(System::Object^  sender, System::EventArgs^  e) { refreshList(); }

	System::Void Window::addLibBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		// I have no idea why you can't just do DialogResult::OK
		if (ofDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
			for each(String^ s in ofDialog->FileNames)
				dllView->Items->Add(gcnew ListViewItem(gcnew array<String^>{ "", s }));
	}

	System::Void Window::advsetBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (advsetBt->Text == "...")
		{
			Window::Size = Drawing::Size(372, 552);
			injPanel->Size = Drawing::Size(359, 180);
			injMethLbl->Visible = true;
			injMethCb->Visible = true;
			procAAChk->Visible = true;
			credLbl->Location = Drawing::Point(3, 130);
			credLbl2->Visible = true;
			advsetBt->Text = ".";
			return;
		}
		if (advsetBt->Text == ".")
		{
			Window::Size = Drawing::Size(372, 451);
			injPanel->Size = Drawing::Size(359, 80);
			injMethLbl->Visible = false;
			injMethCb->Visible = false;
			procAAChk->Visible = false;
			credLbl->Location = Drawing::Point(3, 59);
			credLbl2->Visible = false;
			advsetBt->Text = "...";
			return;
		}
	}

	System::Void Window::injMethCb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if (injMethCb->SelectedIndex == 0)
		{
			hpLbl->Visible = false;
			hpCbx->Visible = false;
			procAAChk->Visible = true;
		}
		if (injMethCb->SelectedIndex == 1)
		{
			hpLbl->Visible = true;
			hpCbx->Visible = true;
			procAAChk->Visible = false;
		}
		if (injMethCb->SelectedIndex == 2)
		{
			MessageBox::Show("This feature has not been fully implemented. (Error code 'lazydev')", "Not yet implemented", MessageBoxButtons::OK, MessageBoxIcon::Error);
			injMethCb->SelectedIndex = 0;
		}
	}

	System::Void Window::injectBt_Click(System::Object^  sender, System::EventArgs^  e)
	{
		for each (ListViewItem^ i in procLV->CheckedItems)
			for each (ListViewItem^ dli in dllView->CheckedItems)
			{
				if (injMethCb->SelectedIndex == 0)
					if (!InjCRT(Convert::ToUInt32(i->SubItems[3]->Text), dli->SubItems[1]->Text, procAAChk->Checked))
						MessageBox::Show("Your DLL has failed to inject. Attempt running Scorpion with elevated privileges or use a different injection method.", "Injection failed!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				if (injMethCb->SelectedIndex == 1)
					if (!InjHWEx(Convert::ToUInt32(i->SubItems[3]->Text), dli->SubItems[1]->Text, hpCbx->SelectedItem->ToString()))
						MessageBox::Show("Your DLL has failed to inject. Attempt running Scorpion with elevated privileges or use a different injection method.", "Injection failed!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}			
	}
}