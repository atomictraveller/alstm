#pragma once

void newmodel() {
	//	'xavier' (glorot) initialisation ideal range is +/- sqrt(6/(inputs+outputs))
	//	eg.	sqrt(6/(96 + 256)) = 0.130558
	//	sqrt(6/(256 + 256)) = 0.10825
	float hisc = 6.f / (float)(idim + hidd);
	float hib = sqrt(hisc);	hisc = hib / 65535.f; hisc += hisc;
	float hhsc = 6.f / (float)(hidd + hidd);
	float hhb = sqrt(hhsc);	hhsc = hhb / 65535.f; hhsc += hhsc;
	for (unsigned int i = 0; i < hidd; i++) for (unsigned int j = 0; j < idim; j++) {
		rnd = 196314165 * rnd + 907633515;  nnh0if[i][j] = (float)(1 + (rnd >> 16)) * hisc - hib;
		rnd = 196314165 * rnd + 907633515;  nnh0ii[i][j] = (float)(1 + (rnd >> 16)) * hisc - hib;
		rnd = 196314165 * rnd + 907633515;  nnh0im[i][j] = (float)(1 + (rnd >> 16)) * hisc - hib;
		rnd = 196314165 * rnd + 907633515;  nnh0io[i][j] = (float)(1 + (rnd >> 16)) * hisc - hib;
	}
	for (unsigned int i = 0; i < hidd; i++) for (unsigned int j = 0; j < hidd; j++) {
		rnd = 196314165 * rnd + 907633515;  nnh0hf[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnh0hi[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnh0hm[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnh0ho[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;

		rnd = 196314165 * rnd + 907633515;  nnhhf[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnhhi[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnhhm[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnhho[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;

		rnd = 196314165 * rnd + 907633515;  nnhif[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnhii[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnhim[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
		rnd = 196314165 * rnd + 907633515;  nnhio[i][j] = (float)(1 + (rnd >> 16)) * hhsc - hhb;
	}
	for (unsigned int i = 0; i < idim; i++) for (unsigned int j = 0; j < hidd; j++) {
		rnd = 196314165 * rnd + 907633515;  nno[i][j] = (float)(1 + (rnd >> 16)) * hisc - hib;	}

	for (unsigned int i = 0; i < hidd; i++) h0fbias[i] = hfbias[i] = 1.f;	//	set forget biases to 1
	memset(h0ibias, 0, sizeof h0ibias);	memset(h0mbias, 0, sizeof h0mbias);	memset(h0obias, 0, sizeof h0obias);	
	memset(hibias, 0, sizeof hibias);	memset(hmbias, 0, sizeof hmbias);	memset(hobias, 0, sizeof hobias);
	memset(obias, 0, sizeof obias);
	adamt = 1;
}

void openmodel() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC ComDlgFS[1] = { {L"data files", L"*.dat"} };
			hr = pFileOpen->SetFileTypes(1, ComDlgFS);
			pFileOpen->SetTitle(L"open model data");
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr)) {
						std::ifstream infile(pszFilePath, std::ios::binary);
						infile.read(reinterpret_cast<char*>(&nnh0hf), sizeof(nnh0hf));
						infile.read(reinterpret_cast<char*>(&nnh0hi), sizeof(nnh0hi));
						infile.read(reinterpret_cast<char*>(&nnh0hm), sizeof(nnh0hm));
						infile.read(reinterpret_cast<char*>(&nnh0ho), sizeof(nnh0ho));
						infile.read(reinterpret_cast<char*>(&nnh0if), sizeof(nnh0if));
						infile.read(reinterpret_cast<char*>(&nnh0ii), sizeof(nnh0ii));
						infile.read(reinterpret_cast<char*>(&nnh0im), sizeof(nnh0im));
						infile.read(reinterpret_cast<char*>(&nnh0io), sizeof(nnh0io));
						infile.read(reinterpret_cast<char*>(&h0fbias), sizeof(h0fbias));
						infile.read(reinterpret_cast<char*>(&h0ibias), sizeof(h0ibias));
						infile.read(reinterpret_cast<char*>(&h0mbias), sizeof(h0mbias));
						infile.read(reinterpret_cast<char*>(&h0obias), sizeof(h0obias));

						infile.read(reinterpret_cast<char*>(&nnhhf), sizeof(nnhhf));
						infile.read(reinterpret_cast<char*>(&nnhhi), sizeof(nnhhi));
						infile.read(reinterpret_cast<char*>(&nnhhm), sizeof(nnhhm));
						infile.read(reinterpret_cast<char*>(&nnhho), sizeof(nnhho));
						infile.read(reinterpret_cast<char*>(&nnhif), sizeof(nnhif));
						infile.read(reinterpret_cast<char*>(&nnhii), sizeof(nnhii));
						infile.read(reinterpret_cast<char*>(&nnhim), sizeof(nnhim));
						infile.read(reinterpret_cast<char*>(&nnhio), sizeof(nnhio));
						infile.read(reinterpret_cast<char*>(&hfbias), sizeof(hfbias));
						infile.read(reinterpret_cast<char*>(&hibias), sizeof(hibias));
						infile.read(reinterpret_cast<char*>(&hmbias), sizeof(hmbias));
						infile.read(reinterpret_cast<char*>(&hobias), sizeof(hobias));

						infile.read(reinterpret_cast<char*>(&nno), sizeof(nno));
						infile.read(reinterpret_cast<char*>(&obias), sizeof(obias));
						infile.close();
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}   pFileOpen->Release();
			}
		}   CoUninitialize();
	}
}

void savemodel() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileSaveDialog* pFileSave;
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC ComDlgFS[1] = { {L"data files", L"*.dat"} };
			hr = pFileSave->SetFileTypes(1, ComDlgFS);
			hr = pFileSave->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr)) {
						// try using fwrite (C) sometime 
						if (!wcsrchr(pszFilePath, L'.')) lstrcat(pszFilePath, L".dat");
						std::ofstream out(pszFilePath, std::ios::binary);
						out.write(reinterpret_cast<char*>(&nnh0hf), sizeof(nnh0hf));
						out.write(reinterpret_cast<char*>(&nnh0hi), sizeof(nnh0hi));
						out.write(reinterpret_cast<char*>(&nnh0hm), sizeof(nnh0hm));
						out.write(reinterpret_cast<char*>(&nnh0ho), sizeof(nnh0ho));
						out.write(reinterpret_cast<char*>(&nnh0if), sizeof(nnh0if));
						out.write(reinterpret_cast<char*>(&nnh0ii), sizeof(nnh0ii));
						out.write(reinterpret_cast<char*>(&nnh0im), sizeof(nnh0im));
						out.write(reinterpret_cast<char*>(&nnh0io), sizeof(nnh0io));
						out.write(reinterpret_cast<char*>(&h0fbias), sizeof(h0fbias));
						out.write(reinterpret_cast<char*>(&h0ibias), sizeof(h0ibias));
						out.write(reinterpret_cast<char*>(&h0mbias), sizeof(h0mbias));
						out.write(reinterpret_cast<char*>(&h0obias), sizeof(h0obias));

						out.write(reinterpret_cast<char*>(&nnhhf), sizeof(nnhhf));
						out.write(reinterpret_cast<char*>(&nnhhi), sizeof(nnhhi));
						out.write(reinterpret_cast<char*>(&nnhhm), sizeof(nnhhm));
						out.write(reinterpret_cast<char*>(&nnhho), sizeof(nnhho));
						out.write(reinterpret_cast<char*>(&nnhif), sizeof(nnhif));
						out.write(reinterpret_cast<char*>(&nnhii), sizeof(nnhii));
						out.write(reinterpret_cast<char*>(&nnhim), sizeof(nnhim));
						out.write(reinterpret_cast<char*>(&nnhio), sizeof(nnhio));
						out.write(reinterpret_cast<char*>(&hfbias), sizeof(hfbias));
						out.write(reinterpret_cast<char*>(&hibias), sizeof(hibias));
						out.write(reinterpret_cast<char*>(&hmbias), sizeof(hmbias));
						out.write(reinterpret_cast<char*>(&hobias), sizeof(hobias));

						out.write(reinterpret_cast<char*>(&nno), sizeof(nno));
						out.write(reinterpret_cast<char*>(&obias), sizeof(obias));
						out.close();
						CoTaskMemFree(pszFilePath);
					}   pItem->Release();
				}
			}   pFileSave->Release();
		}   CoUninitialize();
	}
}

void openadam() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC ComDlgFS[1] = { {L"data files", L"*.dat"} };
			hr = pFileOpen->SetFileTypes(1, ComDlgFS);
			pFileOpen->SetTitle(L"open ADAM data");
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr)) {
						std::ifstream infile(pszFilePath, std::ios::binary);

						infile.read(reinterpret_cast<char*>(&mnno), sizeof(mnno));
						infile.read(reinterpret_cast<char*>(&mobias), sizeof(mobias));

						infile.read(reinterpret_cast<char*>(&mnnh0hf), sizeof(mnnh0hf));
						infile.read(reinterpret_cast<char*>(&mnnh0hi), sizeof(mnnh0hi));
						infile.read(reinterpret_cast<char*>(&mnnh0hm), sizeof(mnnh0hm));
						infile.read(reinterpret_cast<char*>(&mnnh0ho), sizeof(mnnh0ho));
						infile.read(reinterpret_cast<char*>(&mnnh0if), sizeof(mnnh0if));
						infile.read(reinterpret_cast<char*>(&mnnh0ii), sizeof(mnnh0ii));
						infile.read(reinterpret_cast<char*>(&mnnh0im), sizeof(mnnh0im));
						infile.read(reinterpret_cast<char*>(&mnnh0io), sizeof(mnnh0io));
						infile.read(reinterpret_cast<char*>(&mh0fbias), sizeof(mh0fbias));
						infile.read(reinterpret_cast<char*>(&mh0ibias), sizeof(mh0ibias));
						infile.read(reinterpret_cast<char*>(&mh0mbias), sizeof(mh0mbias));
						infile.read(reinterpret_cast<char*>(&mh0obias), sizeof(mh0obias));

						infile.read(reinterpret_cast<char*>(&mnnhhf), sizeof(mnnhhf));
						infile.read(reinterpret_cast<char*>(&mnnhhi), sizeof(mnnhhi));
						infile.read(reinterpret_cast<char*>(&mnnhhm), sizeof(mnnhhm));
						infile.read(reinterpret_cast<char*>(&mnnhho), sizeof(mnnhho));
						infile.read(reinterpret_cast<char*>(&mnnhif), sizeof(mnnhif));
						infile.read(reinterpret_cast<char*>(&mnnhii), sizeof(mnnhii));
						infile.read(reinterpret_cast<char*>(&mnnhim), sizeof(mnnhim));
						infile.read(reinterpret_cast<char*>(&mnnhio), sizeof(mnnhio));
						infile.read(reinterpret_cast<char*>(&mhfbias), sizeof(mhfbias));
						infile.read(reinterpret_cast<char*>(&mhibias), sizeof(mhibias));
						infile.read(reinterpret_cast<char*>(&mhmbias), sizeof(mhmbias));
						infile.read(reinterpret_cast<char*>(&mhobias), sizeof(mhobias));


						infile.read(reinterpret_cast<char*>(&vnno), sizeof(vnno));
						infile.read(reinterpret_cast<char*>(&vobias), sizeof(vobias));

						infile.read(reinterpret_cast<char*>(&vnnh0hf), sizeof(vnnh0hf));
						infile.read(reinterpret_cast<char*>(&vnnh0hi), sizeof(vnnh0hi));
						infile.read(reinterpret_cast<char*>(&vnnh0hm), sizeof(vnnh0hm));
						infile.read(reinterpret_cast<char*>(&vnnh0ho), sizeof(vnnh0ho));
						infile.read(reinterpret_cast<char*>(&vnnh0if), sizeof(vnnh0if));
						infile.read(reinterpret_cast<char*>(&vnnh0ii), sizeof(vnnh0ii));
						infile.read(reinterpret_cast<char*>(&vnnh0im), sizeof(vnnh0im));
						infile.read(reinterpret_cast<char*>(&vnnh0io), sizeof(vnnh0io));
						infile.read(reinterpret_cast<char*>(&vh0fbias), sizeof(vh0fbias));
						infile.read(reinterpret_cast<char*>(&vh0ibias), sizeof(vh0ibias));
						infile.read(reinterpret_cast<char*>(&vh0mbias), sizeof(vh0mbias));
						infile.read(reinterpret_cast<char*>(&vh0obias), sizeof(vh0obias));

						infile.read(reinterpret_cast<char*>(&vnnhhf), sizeof(vnnhhf));
						infile.read(reinterpret_cast<char*>(&vnnhhi), sizeof(vnnhhi));
						infile.read(reinterpret_cast<char*>(&vnnhhm), sizeof(vnnhhm));
						infile.read(reinterpret_cast<char*>(&vnnhho), sizeof(vnnhho));
						infile.read(reinterpret_cast<char*>(&vnnhif), sizeof(vnnhif));
						infile.read(reinterpret_cast<char*>(&vnnhii), sizeof(vnnhii));
						infile.read(reinterpret_cast<char*>(&vnnhim), sizeof(vnnhim));
						infile.read(reinterpret_cast<char*>(&vnnhio), sizeof(vnnhio));
						infile.read(reinterpret_cast<char*>(&vhfbias), sizeof(vhfbias));
						infile.read(reinterpret_cast<char*>(&vhibias), sizeof(vhibias));
						infile.read(reinterpret_cast<char*>(&vhmbias), sizeof(vhmbias));
						infile.read(reinterpret_cast<char*>(&vhobias), sizeof(vhobias));

						infile.close();
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}   pFileOpen->Release();
			}
		}   CoUninitialize();
	}
}

void saveadam() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileSaveDialog* pFileSave;
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC ComDlgFS[1] = { {L"data files", L"*.dat"} };
			hr = pFileSave->SetFileTypes(1, ComDlgFS);
			hr = pFileSave->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr)) {
						if (!wcsrchr(pszFilePath, L'.')) lstrcat(pszFilePath, L".dat");
						std::ofstream out(pszFilePath, std::ios::binary);

						out.write(reinterpret_cast<char*>(&mnno), sizeof(mnno));
						out.write(reinterpret_cast<char*>(&mobias), sizeof(mobias));

						out.write(reinterpret_cast<char*>(&mnnh0hf), sizeof(mnnh0hf));
						out.write(reinterpret_cast<char*>(&mnnh0hi), sizeof(mnnh0hi));
						out.write(reinterpret_cast<char*>(&mnnh0hm), sizeof(mnnh0hm));
						out.write(reinterpret_cast<char*>(&mnnh0ho), sizeof(mnnh0ho));
						out.write(reinterpret_cast<char*>(&mnnh0if), sizeof(mnnh0if));
						out.write(reinterpret_cast<char*>(&mnnh0ii), sizeof(mnnh0ii));
						out.write(reinterpret_cast<char*>(&mnnh0im), sizeof(mnnh0im));
						out.write(reinterpret_cast<char*>(&mnnh0io), sizeof(mnnh0io));
						out.write(reinterpret_cast<char*>(&mh0fbias), sizeof(mh0fbias));
						out.write(reinterpret_cast<char*>(&mh0ibias), sizeof(mh0ibias));
						out.write(reinterpret_cast<char*>(&mh0mbias), sizeof(mh0mbias));
						out.write(reinterpret_cast<char*>(&mh0obias), sizeof(mh0obias));

						out.write(reinterpret_cast<char*>(&mnnhhf), sizeof(mnnhhf));
						out.write(reinterpret_cast<char*>(&mnnhhi), sizeof(mnnhhi));
						out.write(reinterpret_cast<char*>(&mnnhhm), sizeof(mnnhhm));
						out.write(reinterpret_cast<char*>(&mnnhho), sizeof(mnnhho));
						out.write(reinterpret_cast<char*>(&mnnhif), sizeof(mnnhif));
						out.write(reinterpret_cast<char*>(&mnnhii), sizeof(mnnhii));
						out.write(reinterpret_cast<char*>(&mnnhim), sizeof(mnnhim));
						out.write(reinterpret_cast<char*>(&mnnhio), sizeof(mnnhio));
						out.write(reinterpret_cast<char*>(&mhfbias), sizeof(mhfbias));
						out.write(reinterpret_cast<char*>(&mhibias), sizeof(mhibias));
						out.write(reinterpret_cast<char*>(&mhmbias), sizeof(mhmbias));
						out.write(reinterpret_cast<char*>(&mhobias), sizeof(mhobias));


						out.write(reinterpret_cast<char*>(&vnno), sizeof(vnno));
						out.write(reinterpret_cast<char*>(&vobias), sizeof(vobias));

						out.write(reinterpret_cast<char*>(&vnnh0hf), sizeof(vnnh0hf));
						out.write(reinterpret_cast<char*>(&vnnh0hi), sizeof(vnnh0hi));
						out.write(reinterpret_cast<char*>(&vnnh0hm), sizeof(vnnh0hm));
						out.write(reinterpret_cast<char*>(&vnnh0ho), sizeof(vnnh0ho));
						out.write(reinterpret_cast<char*>(&vnnh0if), sizeof(vnnh0if));
						out.write(reinterpret_cast<char*>(&vnnh0ii), sizeof(vnnh0ii));
						out.write(reinterpret_cast<char*>(&vnnh0im), sizeof(vnnh0im));
						out.write(reinterpret_cast<char*>(&vnnh0io), sizeof(vnnh0io));
						out.write(reinterpret_cast<char*>(&vh0fbias), sizeof(vh0fbias));
						out.write(reinterpret_cast<char*>(&vh0ibias), sizeof(vh0ibias));
						out.write(reinterpret_cast<char*>(&vh0mbias), sizeof(vh0mbias));
						out.write(reinterpret_cast<char*>(&vh0obias), sizeof(vh0obias));

						out.write(reinterpret_cast<char*>(&vnnhhf), sizeof(vnnhhf));
						out.write(reinterpret_cast<char*>(&vnnhhi), sizeof(vnnhhi));
						out.write(reinterpret_cast<char*>(&vnnhhm), sizeof(vnnhhm));
						out.write(reinterpret_cast<char*>(&vnnhho), sizeof(vnnhho));
						out.write(reinterpret_cast<char*>(&vnnhif), sizeof(vnnhif));
						out.write(reinterpret_cast<char*>(&vnnhii), sizeof(vnnhii));
						out.write(reinterpret_cast<char*>(&vnnhim), sizeof(vnnhim));
						out.write(reinterpret_cast<char*>(&vnnhio), sizeof(vnnhio));
						out.write(reinterpret_cast<char*>(&vhfbias), sizeof(vhfbias));
						out.write(reinterpret_cast<char*>(&vhibias), sizeof(vhibias));
						out.write(reinterpret_cast<char*>(&vhmbias), sizeof(vhmbias));
						out.write(reinterpret_cast<char*>(&vhobias), sizeof(vhobias));

						out.close();
						CoTaskMemFree(pszFilePath);
					}   pItem->Release();
				}
			}   pFileSave->Release();
		}   CoUninitialize();
	}
}

typedef struct {
	unsigned short int format;       // PCM = 1
	unsigned short int channels;
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned short int blockAlign;
	unsigned short int bitsPerSample;
} WavFmt;

WavFmt fmt;	void* samples;	unsigned long int size;	short int* s;

int openwav(const char* filename, WavFmt* fmt, void** data, unsigned long int* dataSize) {
    HANDLE h = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) return 0;
    DWORD read;   char tag[4];
    if (!ReadFile(h, tag, 4, &read, NULL) || memcmp(tag, "RIFF", 4)) { CloseHandle(h); return -1; }
    SetFilePointer(h, 4, NULL, FILE_CURRENT);	// skip total file size
    if (!ReadFile(h, tag, 4, &read, NULL) || memcmp(tag, "WAVE", 4)) { CloseHandle(h); return -1; }
    while (true) {
        unsigned long int chunkSize;
        if (!ReadFile(h, tag, 4, &read, NULL) || read < 4) break; // eof or error
        if (!ReadFile(h, &chunkSize, 4, &read, NULL) || read < 4) break;
        if (!memcmp(tag, "fmt ", 4)) {
            DWORD sizeToRead = (chunkSize < sizeof(WavFmt)) ? chunkSize : sizeof(WavFmt);
            ReadFile(h, fmt, sizeToRead, &read, NULL);
            SetFilePointer(h, chunkSize - read, NULL, FILE_CURRENT); }
        else if (!memcmp(tag, "data", 4)) {
            *dataSize = chunkSize;
            *data = VirtualAlloc(0, chunkSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (!*data) { CloseHandle(h); return -2; }         
            if (!ReadFile(h, *data, chunkSize, &read, NULL) || read < chunkSize) {
                VirtualFree(*data, 0, MEM_RELEASE);
                CloseHandle(h);	return -3; }
            CloseHandle(h);	return 1; }
        else SetFilePointer(h, chunkSize, NULL, FILE_CURRENT);	//	skip unknown chunk
    }
    CloseHandle(h);	return -3;	//	reached eof without finding data chunk
}


void selectwav() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);		//	populate filepath
	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC ComDlgFS[1] = { {L"wav files", L"*.wav"} };
			hr = pFileOpen->SetFileTypes(1, ComDlgFS);
			pFileOpen->SetTitle(L"open wav file");
			hr = pFileOpen->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr)) {
						WideCharToMultiByte(CP_ACP, 0, pszFilePath, -1, wavpath, MAX_PATH, NULL, NULL);
						char thiswav = openwav(wavpath, &fmt, &samples, &size);
						if (!samples || size == 0) wavsamples = 0;
						else {
							wavsamples = size / (fmt.bitsPerSample >> 3);
							if (fmt.channels == 2) {
								stereo = 1;	//	read left then right samples
								wavsamples >>= 1;
							}
							else stereo = 0;
							s = (short int*)samples;
						}	CoTaskMemFree(pszFilePath);
					}	pItem->Release();
				}   pFileOpen->Release();
			}
		}   CoUninitialize();
	}
}

bool writewav() {	//	base function, makes wavs of 0 data atm
	memset(sout, 0, sizeof sout);
	HANDLE h = CreateFileA("output.wav", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h!= INVALID_HANDLE_VALUE) {

		unsigned int datasize = 0;
		unsigned int filesize = datasize + 36;	//	rest of file size in bytes eg. total size - 8
		unsigned int fsize = 16;	//	size of format block in bits
		unsigned short wfmt = 1;	//	1 = PCM format
		unsigned short nchan = 1;
		unsigned int fsrate = 44100;
		unsigned int brate = fsrate * 2;	//	bytes per second
		unsigned short blockalign = nchan * 2;	//	channels * bytes per sample
		unsigned short bitspersample = 16;

		DWORD nowt;	//	"how many bytes i actually copied!"
		WriteFile(h, "RIFF", 4, &nowt, NULL);
		WriteFile(h, &filesize, 4, &nowt, NULL);
		WriteFile(h, "WAVEfmt ", 8, &nowt, NULL);	//	hah!

		WriteFile(h, &fsize, 4, &nowt, NULL);
		WriteFile(h, &wfmt, 2, &nowt, NULL);
		WriteFile(h, &nchan, 2, &nowt, NULL);
		WriteFile(h, &fsrate, 4, &nowt, NULL);
		WriteFile(h, &brate, 4, &nowt, NULL);
		WriteFile(h, &blockalign, 2, &nowt, NULL);
		WriteFile(h, &bitspersample, 2, &nowt, NULL);

		WriteFile(h, "data", 4, &nowt, NULL);
		WriteFile(h, &datasize, 4, &nowt, NULL);

		CloseHandle(h);
	}
	return 0;

}





void sampleoutput(HWND hWnd) {
	memset(h, 0, sizeof h);	memset(c, 0, sizeof c);
	memset(h0, 0, sizeof h0);	memset(c0, 0, sizeof c0);
	action = 2;
	
//	for (int i = 0; i < winm; i++) for (int j = 0; j < hidd; j++) {
//		rnd = 196314165 * rnd + 907633515;	h[i][j] = (float)(rnd >> 16) * 1.5259e-6f - 0.05f;
//		rnd = 196314165 * rnd + 907633515;	c[i][j] = (float)(rnd >> 16) * 1.5259e-6f - 0.05f;
//		rnd = 196314165 * rnd + 907633515;	h0[i][j] = (float)(rnd >> 16) * 1.5259e-6f - 0.05f;
//		rnd = 196314165 * rnd + 907633515;	c0[i][j] = (float)(rnd >> 16) * 1.5259e-6f - 0.05f;
//	}
	
	memset(out1, 0, sizeof out1);
//	sb = 0.f;
	rnd = 196314165 * rnd + 907633515;	sb = (float)(rnd >> 16) * 1.5259e-6f - 0.05f;

	tests = 0;
	audition = 1;
	while ((tests < OUT_BUFFER_SIZE) && audition) {

		char twin = tests & winm;
		char tprev = (twin + winm) & winm;	//	twin previous step

		float st = sb;

		for (unsigned int i = 0; i < hidd; i++) {	//	forget gate						HIDDEN LAYER 1
			float sum = h0fbias[i];
			sum += nnh0if[i][0] * st;
			for (unsigned int j = 0; j < hidd; j++) sum += nnh0hf[i][j] * h0[tprev][j];
			h0f[twin][i] = sum = 1.f + exp(-sum);
			c0[twin][i] = c0[tprev][i] / sum;
		}
		for (unsigned int i = 0; i < hidd; i++) {	//	input gate
			float sum = h0ibias[i];	//	input gate
			sum += nnh0ii[i][0] * st;
			for (unsigned int j = 0; j < hidd; j++) sum += nnh0hi[i][j] * h0[tprev][j];
			h0i[twin][i] = sum = 1.f / (1.f + exp(-sum));
			float sum2 = h0mbias[i];	//	input node/potential memory
			sum2 += nnh0im[i][0] * st;
			for (unsigned int j = 0; j < hidd; j++) sum2 += nnh0hm[i][j] * h0[tprev][j];
			h0m[twin][i] = sum2 = tanh(sum2);
			c0[twin][i] += sum * sum2;
		}
		for (unsigned int i = 0; i < hidd; i++) {	//	output gate
			float sum = h0obias[i];
			sum += nnh0io[i][0] * st;
			for (unsigned int j = 0; j < hidd; j++) sum += nnh0ho[i][j] * h0[tprev][j];
			h0o[twin][i] = sum = 1.f + exp(-sum);
			h0[twin][i] = tanh(c0[twin][i]) / sum;
		}

		for (unsigned int i = 0; i < hidd; i++) {	//	forget gate						HIDDEN LAYER 2
			float sum = hfbias[i];
			for (unsigned int j = 0; j < hidd; j++) sum += nnhif[i][j] * h0[twin][j];
			for (unsigned int j = 0; j < hidd; j++) sum += nnhhf[i][j] * h[tprev][j];
			hf[twin][i] = sum = 1.f + exp(-sum);
			c[twin][i] = c[tprev][i] / sum;
		}
		for (unsigned int i = 0; i < hidd; i++) {	//	input gate
			float sum = hibias[i];	//	input gate
			for (unsigned int j = 0; j < hidd; j++) sum += nnhii[i][j] * h0[twin][j];
			for (unsigned int j = 0; j < hidd; j++) sum += nnhhi[i][j] * h[tprev][j];
			hi[twin][i] = sum = 1.f / (1.f + exp(-sum));
			float sum2 = hmbias[i];	//	input node/potential memory
			for (unsigned int j = 0; j < hidd; j++) sum2 += nnhim[i][j] * h0[twin][j];
			for (unsigned int j = 0; j < hidd; j++) sum2 += nnhhm[i][j] * h[tprev][j];
			hm[twin][i] = sum2 = tanh(sum2);
			c[twin][i] += sum * sum2;
		}
		for (unsigned int i = 0; i < hidd; i++) {	//	output gate
			float sum = hobias[i];
			for (unsigned int j = 0; j < hidd; j++) sum += nnhio[i][j] * h0[twin][j];
			for (unsigned int j = 0; j < hidd; j++) sum += nnhho[i][j] * h[tprev][j];
			ho[twin][i] = sum = 1.f + exp(-sum);
			h[twin][i] = tanh(c[twin][i]) / sum;
		}

		for (int i = 0; i < idim; i++) {
			float sum = obias[i];
			for (unsigned int j = 0; j < hidd; j++) sum += nno[i][j] * h[twin][j];
			netout[twin][i] = sum;
		}
		sb = netout[twin][0];

		out1[tests] = fmin(1.f, fmax(-1.f, sb)) * 32768.f;	//	put sample to 'display' buffer

		tests++;

		if (!(tests & 255)) {
			InvalidateRgn(hWnd, 0, 0);	UpdateWindow(hWnd);
			MSG tmsg;
			while (PeekMessage(&tmsg, hWnd, 0, 0, PM_REMOVE)) { TranslateMessage(&tmsg); DispatchMessage(&tmsg); }
		}

		tests &= 16383;
	}
	action = 0;
}










void train(HWND hWnd) {
	action = 1;
	thismany = 0;
	while (thismany < 1 + ((int)do10x * 9)) {
		memset(h, 0, sizeof h);	memset(c, 0, sizeof c);
		memset(h0, 0, sizeof h0);	memset(c0, 0, sizeof c0);

		dispix++;	if (dispix > 9) dispix = 0;	//	for stepping through display colors
		ebuf = 0.f;
		tests = 0;

		while (((tests << 2) < wavsamples) && !stop) {
			int twin = tests & winm;	//	truncated rnn windowing for indefinite serial processing
			int tprev = (twin + winm) & winm;	//	twin previous step
		
			float st = stereo ? (float)s[(tests << 3)] : (float)s[(tests << 2)];	//	input sample
			st *= 0.000030517578125f;	//	scale sample for net
			samplein[twin] = sb;

			for (unsigned int i = 0; i < hidd; i++) {	//	forget gate						HIDDEN LAYER 1
				float sum = h0fbias[i];
			//	for (unsigned int j = 0; j < idim; j++) sum += nnh0if[i][j] * netin[j];	//	theory
				sum += nnh0if[i][0] * st;
				for (unsigned int j = 0; j < hidd; j++) sum += nnh0hf[i][j] * h0[tprev][j];
				h0f[twin][i] = sum = 1.f + exp(-sum);
				c0[twin][i] = c0[tprev][i] / sum;
			}
			for (unsigned int i = 0; i < hidd; i++) {	//	input gate
				float sum = h0ibias[i];	//	input gate
				sum += nnh0ii[i][0] * st;
				for (unsigned int j = 0; j < hidd; j++) sum += nnh0hi[i][j] * h0[tprev][j];
				h0i[twin][i] = sum = 1.f / (1.f + exp(-sum));
				float sum2 = h0mbias[i];	//	input node/potential memory
				sum2 += nnh0im[i][0] * st;
				for (unsigned int j = 0; j < hidd; j++) sum2 += nnh0hm[i][j] * h0[tprev][j];
				h0m[twin][i] = sum2 = tanh(sum2);
				c0[twin][i] += sum * sum2;
			}
			for (unsigned int i = 0; i < hidd; i++) {	//	output gate
				float sum = h0obias[i];
				sum += nnh0io[i][0] * st;
				for (unsigned int j = 0; j < hidd; j++) sum += nnh0ho[i][j] * h0[tprev][j];
				h0o[twin][i] = sum = 1.f + exp(-sum);
				h0[twin][i] = tanh(c0[twin][i]) / sum;
			}

			for (unsigned int i = 0; i < hidd; i++) {	//	forget gate						HIDDEN LAYER 2
				float sum = hfbias[i];
				for (unsigned int j = 0; j < hidd; j++) sum += nnhif[i][j] * h0[twin][j];
				for (unsigned int j = 0; j < hidd; j++) sum += nnhhf[i][j] * h[tprev][j];
				hf[twin][i] = sum = 1.f + exp(-sum);
				c[twin][i] = c[tprev][i] / sum;
			}
			for (unsigned int i = 0; i < hidd; i++) {	//	input gate
				float sum = hibias[i];	//	input gate
				for (unsigned int j = 0; j < hidd; j++) sum += nnhii[i][j] * h0[twin][j];
				for (unsigned int j = 0; j < hidd; j++) sum += nnhhi[i][j] * h[tprev][j];
				hi[twin][i] = sum = 1.f / (1.f + exp(-sum));
				float sum2 = hmbias[i];	//	input node/potential memory
				for (unsigned int j = 0; j < hidd; j++) sum2 += nnhim[i][j] * h0[twin][j];
				for (unsigned int j = 0; j < hidd; j++) sum2 += nnhhm[i][j] * h[tprev][j];
				hm[twin][i] = sum2 = tanh(sum2);
				c[twin][i] += sum * sum2;
			}
			for (unsigned int i = 0; i < hidd; i++) {	//	output gate
				float sum = hobias[i];
				for (unsigned int j = 0; j < hidd; j++) sum += nnhio[i][j] * h0[twin][j];
				for (unsigned int j = 0; j < hidd; j++) sum += nnhho[i][j] * h[tprev][j];
				ho[twin][i] = sum = 1.f + exp(-sum);
				h[twin][i] = tanh(c[twin][i]) / sum;
			}

			for (int i = 0; i < idim; i++) {
				float sum = obias[i];
				for (unsigned int j = 0; j < hidd; j++) sum += nno[i][j] * h[twin][j];
				netout[twin][i] = sum;
			}

			out1[(tests & 16383)] = fmin(1.f, fmax(-1.f, netout[twin][0])) * 32768.f;	//	put sample to 'display' buffer

			netout[twin][0] -= st;	//	subtract appropriate target from each prediction

			ebuf -= log(fmax(1e-18f, fabs(netout[twin][0])));	//	-logf(netout[twin][tc] + 1e-12f);
		//	ebuf -= log(fmax(1e-18f, 0.5f * netout[twin][0] * netout[twin][0]));	//	above 'looks more familiar'
			edisp = ebuf / (float)max(1, tests);

			if (twin == winm) {	//	eg. "63 of 63" do BPTT
				memset(dnno, 0, sizeof dnno);
				memset(dobias, 0, sizeof dobias);
				memset(dh0_next, 0, sizeof dh0_next);	memset(dc0_next, 0, sizeof(dc0_next));
				memset(dh0, 0, sizeof dh0);
				memset(dnnh0hf, 0, sizeof dnnh0hf);	memset(dnnh0hi, 0, sizeof dnnh0hi);
				memset(dnnh0hm, 0, sizeof dnnh0hm);	memset(dnnh0ho, 0, sizeof dnnh0ho);
				memset(dnnh0if, 0, sizeof dnnh0if);	memset(dnnh0ii, 0, sizeof dnnh0ii);
				memset(dnnh0im, 0, sizeof dnnh0im);	memset(dnnh0io, 0, sizeof dnnh0io);
				memset(dh0fbias, 0, sizeof dh0fbias);	memset(dh0ibias, 0, sizeof dh0ibias);
				memset(dh0mbias, 0, sizeof dh0mbias);	memset(dh0obias, 0, sizeof dh0obias);

				memset(dh_next, 0, sizeof dh_next);	memset(dc_next, 0, sizeof(dc_next));
				memset(dh, 0, sizeof dh);
				memset(dnnhhf, 0, sizeof dnnhhf);	memset(dnnhhi, 0, sizeof dnnhhi);
				memset(dnnhhm, 0, sizeof dnnhhm);	memset(dnnhho, 0, sizeof dnnhho);
				memset(dnnhif, 0, sizeof dnnhif);	memset(dnnhii, 0, sizeof dnnhii);
				memset(dnnhim, 0, sizeof dnnhim);	memset(dnnhio, 0, sizeof dnnhio);
				memset(dhfbias, 0, sizeof dhfbias);	memset(dhibias, 0, sizeof dhibias);
				memset(dhmbias, 0, sizeof dhmbias);	memset(dhobias, 0, sizeof dhobias);

				for (int iter = winm; iter > -1; iter--) {		//	BPTT 'back propogation through time'
					int iprev = (bool)iter ? iter - 1 : wind;
					for (unsigned int i = 0; i < idim; i++) {
						dobias[i] += netout[iter][i];
						for (unsigned int j = 0; j < hidd; j++) dnno[i][j] += netout[iter][i] * h[iter][j];
					}
					for (int i = 0; i < hidd; i++) {
						float sum = dh_next[i];
						for (int j = 0; j < idim; j++) sum += nno[j][i] * netout[iter][j];
						dh[i] = sum;
					}
					for (int i = 0; i < hidd; i++) {
						float tanh_c = tanh(c[iter][i]);
						float dc_total = dc_next[i] + (dh[i] * ho[iter][i] * (1.f - tanh_c * tanh_c));
						float df_raw = dc_total * c[iprev][i] * (hf[iter][i] * (1.f - hf[iter][i]));
						float di_raw = dc_total * hm[iter][i] * (hi[iter][i] * (1.f - hi[iter][i]));
						float dm_raw = dc_total * hi[iter][i] * (1.f - hm[iter][i] * hm[iter][i]);
						float do_raw = dh[i] * tanh_c * (ho[iter][i] * (1.f - ho[iter][i]));
						dhf_raw[i] = df_raw;	dhi_raw[i] = di_raw;	dhm_raw[i] = dm_raw;	dho_raw[i] = do_raw;
						dhfbias[i] += df_raw;	dhibias[i] += di_raw;	dhmbias[i] += dm_raw;	dhobias[i] += do_raw;
						for (unsigned int j = 0; j < hidd; j++) {							
							dnnhhf[i][j] += df_raw * h[iprev][j];
							dnnhhi[i][j] += di_raw * h[iprev][j];
							dnnhhm[i][j] += dm_raw * h[iprev][j];
							dnnhho[i][j] += do_raw * h[iprev][j];
							dnnhif[i][j] += df_raw * h0[iter][j];
							dnnhii[i][j] += di_raw * h0[iter][j];
							dnnhim[i][j] += dm_raw * h0[iter][j];
							dnnhio[i][j] += do_raw * h0[iter][j];
						}						
						dc_next[i] = dc_total * hf[iter][i];
					}
					for (unsigned int j = 0; j < hidd; j++) {
						float sum = dh0_next[j];
						for (int i = 0; i < hidd; i++) sum += nnhif[i][j] * dhf_raw[i] + nnhii[i][j] * dhi_raw[i]
							+ nnhim[i][j] * dhm_raw[i] + nnhio[i][j] * dho_raw[i];
						dh0[j] = sum;
					}
					float sref = samplein[iter];
					for (int i = 0; i < hidd; i++) {
						float tanh_c = tanh(c0[iter][i]);
						float dc_total = dc0_next[i] + (dh0[i] * h0o[iter][i] * (1.f - tanh_c * tanh_c));
						float df_raw = dc_total * c0[iprev][i] * (h0f[iter][i] * (1.f - h0f[iter][i]));
						float di_raw = dc_total * h0m[iter][i] * (h0i[iter][i] * (1.f - h0i[iter][i]));
						float dm_raw = dc_total * h0i[iter][i] * (1.f - h0m[iter][i] * h0m[iter][i]);
						float do_raw = dh0[i] * tanh_c * (h0o[iter][i] * (1.f - h0o[iter][i]));
						dh0f_raw[i] = df_raw;	dh0i_raw[i] = di_raw;	dh0m_raw[i] = dm_raw;	dh0o_raw[i] = do_raw;
						dh0fbias[i] += df_raw;	dh0ibias[i] += di_raw;	dh0mbias[i] += dm_raw;	dh0obias[i] += do_raw;
						dnnh0if[i][0] += df_raw * sref;	//	single node input layer
						dnnh0ii[i][0] += di_raw * sref;
						dnnh0im[i][0] += dm_raw * sref;
						dnnh0io[i][0] += do_raw * sref;
						for (unsigned int j = 0; j < hidd; j++) {							
							dnnh0hf[i][j] += df_raw * h0[iprev][j];
							dnnh0hi[i][j] += di_raw * h0[iprev][j];
							dnnh0hm[i][j] += dm_raw * h0[iprev][j];
							dnnh0ho[i][j] += do_raw * h0[iprev][j];
						}				
						dc0_next[i] = dc_total * h0f[iter][i];
					}
					for (int i = 0; i < hidd; i++) {
						float sum0 = 0.f;    float sum = 0.f;
						for (int j = 0; j < hidd; j++) {
							sum0 += nnh0hf[j][i] * dh0f_raw[j] + nnh0hi[j][i] * dh0i_raw[j] +
								nnh0hm[j][i] * dh0m_raw[j] + nnh0ho[j][i] * dh0o_raw[j];
							sum += nnhhf[j][i] * dhf_raw[j] + nnhhi[j][i] * dhi_raw[j] +
								nnhhm[j][i] * dhm_raw[j] + nnhho[j][i] * dho_raw[j];
						}
						dh0_next[i] = sum0;
						dh_next[i] = sum;
					}

				}				
				memcpy(h0[wind], h0[winm], sizeof h0[wind]);	memcpy(h[wind], h[winm], sizeof h[wind]);
				memcpy(c0[wind], c0[winm], sizeof c0[wind]);	memcpy(c[wind], c[winm], sizeof c[wind]);
				//	after tBPTT copy next round's h[-1] to h[wind] 	to solve buffer for windowed forwards and backwards processing

				if (GRADNORM) {
					float norm = 0.f;		//	gradient normalisation
					float clip = 1.f;

					for (int i = 0; i < idim; i++) {
						norm += dobias[i] * dobias[i];
						for (int j = 0; j < hidd; j++) {
							norm += dnnh0if[j][i] * dnnh0if[j][i];	//	switch this in lstm
							norm += dnnh0ii[j][i] * dnnh0ii[j][i];
							norm += dnnh0im[j][i] * dnnh0im[j][i];
							norm += dnnh0io[j][i] * dnnh0io[j][i];
					}	}
					for (int i = 0; i < hidd; i++) {
						for (int j = 0; j < hidd; j++) {
							norm += dnnh0hf[i][j] * dnnh0hf[i][j];
							norm += dnnh0hi[i][j] * dnnh0hi[i][j];
							norm += dnnh0hm[i][j] * dnnh0hm[i][j];
							norm += dnnh0ho[i][j] * dnnh0ho[i][j];
							norm += dnnhhf[i][j] * dnnhhf[i][j];
							norm += dnnhhi[i][j] * dnnhhi[i][j];
							norm += dnnhhm[i][j] * dnnhhm[i][j];
							norm += dnnhho[i][j] * dnnhho[i][j];
							norm += dnnhif[i][j] * dnnhif[i][j];
							norm += dnnhii[i][j] * dnnhii[i][j];
							norm += dnnhim[i][j] * dnnhim[i][j];
							norm += dnnhio[i][j] * dnnhio[i][j];
						}
						for (int j = 0; j < idim; j++) norm += dnno[j][i] * dnno[j][i];	//	switch this one line in lstm
						norm += dh0fbias[i] * dh0fbias[i];
						norm += dh0ibias[i] * dh0ibias[i];
						norm += dh0mbias[i] * dh0mbias[i];
						norm += dh0obias[i] * dh0obias[i];
						norm += dhfbias[i] * dhfbias[i];
						norm += dhibias[i] * dhibias[i];
						norm += dhmbias[i] * dhmbias[i];
						norm += dhobias[i] * dhobias[i];
					}
					if (norm > clip) {
						norm = clip / sqrt(norm);
						for (int i = 0; i < idim; i++) {
							dobias[i] *= norm;
							for (int j = 0; j < hidd; j++) {	//	change these 4 in lstm
								dnnh0if[j][i] *= norm;	dnnh0ii[j][i] *= norm;	dnnh0im[j][i] *= norm;	dnnh0io[j][i] *= norm;
						}	}
						for (int i = 0; i < hidd; i++) {
							for (int j = 0; j < hidd; j++) {
								dnnh0hf[i][j] *= norm;	dnnh0hi[i][j] *= norm;	dnnh0hm[i][j] *= norm;	dnnh0ho[i][j] *= norm;
								dnnhhf[i][j] *= norm;	dnnhhi[i][j] *= norm;	dnnhhm[i][j] *= norm;	dnnhho[i][j] *= norm;
								dnnhif[i][j] *= norm;	dnnhii[i][j] *= norm;	dnnhim[i][j] *= norm;	dnnhio[i][j] *= norm;
							}
							for (int j = 0; j < idim; j++) dnno[j][i] *= norm;	//	switch this one line in lstm
							dh0fbias[i] *= norm;	dh0ibias[i] *= norm;	dh0mbias[i] *= norm;	dh0obias[i] *= norm;
							dhfbias[i] *= norm;		dhibias[i] *= norm;		dhmbias[i] *= norm;		dhobias[i] *= norm;
					}	}
				}
				else {	//	else clip gradients
					register float clip = 1.f;
					for (int i = 0; i < idim; i++) {	//	gradient clipping
						for (int j = 0; j < hidd; j++) {
							dnno[i][j] = fmax(-clip, fmin(clip, dnno[i][j]));	//	all 5 switched
							dnnh0if[j][i] = fmax(-clip, fmin(clip, dnnh0if[j][i]));
							dnnh0ii[j][i] = fmax(-clip, fmin(clip, dnnh0ii[j][i]));
							dnnh0im[j][i] = fmax(-clip, fmin(clip, dnnh0im[j][i]));
							dnnh0io[j][i] = fmax(-clip, fmin(clip, dnnh0io[j][i]));
						}
						dobias[i] = fmax(-clip, fmin(clip, dobias[i]));
					}
					for (int i = 0; i < hidd; i++) {
						dh0fbias[i] = fmax(-clip, fmin(clip, dh0fbias[i]));
						dh0ibias[i] = fmax(-clip, fmin(clip, dh0ibias[i]));
						dh0mbias[i] = fmax(-clip, fmin(clip, dh0mbias[i]));
						dh0obias[i] = fmax(-clip, fmin(clip, dh0obias[i]));
						dhfbias[i] = fmax(-clip, fmin(clip, dhfbias[i]));
						dhibias[i] = fmax(-clip, fmin(clip, dhibias[i]));
						dhmbias[i] = fmax(-clip, fmin(clip, dhmbias[i]));
						dhobias[i] = fmax(-clip, fmin(clip, dhobias[i]));
						for (int j = 0; j < hidd; j++) {
							dnnh0hf[i][j] = fmax(-clip, fmin(clip, dnnh0hf[i][j]));
							dnnh0hi[i][j] = fmax(-clip, fmin(clip, dnnh0hi[i][j]));
							dnnh0hm[i][j] = fmax(-clip, fmin(clip, dnnh0hm[i][j]));
							dnnh0ho[i][j] = fmax(-clip, fmin(clip, dnnh0ho[i][j]));
							dnnhhf[i][j] = fmax(-clip, fmin(clip, dnnhhf[i][j]));
							dnnhhi[i][j] = fmax(-clip, fmin(clip, dnnhhi[i][j]));
							dnnhhm[i][j] = fmax(-clip, fmin(clip, dnnhhm[i][j]));
							dnnhho[i][j] = fmax(-clip, fmin(clip, dnnhho[i][j]));
							dnnhif[i][j] = fmax(-clip, fmin(clip, dnnhif[i][j]));
							dnnhii[i][j] = fmax(-clip, fmin(clip, dnnhii[i][j]));
							dnnhim[i][j] = fmax(-clip, fmin(clip, dnnhim[i][j]));
							dnnhio[i][j] = fmax(-clip, fmin(clip, dnnhio[i][j]));
					}	}
				}

				register float learn = learnarr[learnix] * temparr[tempix];
				if (ADAM) {
					float mbiascorr = (float)(1.0 / (1.0 - pow((double)beta1, adamt)));
					float vbiascorr = (float)(1.0 / (1.0 - pow((double)beta2, adamt)));
					adamt++;
					learn *= 0.125f;

					for (unsigned int i = 0; i < hidd; i++) {   // update weights using ADAM optimisation
						register float vcorr;
						for (unsigned int j = 0; j < idim; j++) {
							mnno[j][i] += beta1m * (dnno[j][i] - mnno[j][i]);	//	4 lines switched
							vnno[j][i] += beta2m * (dnno[j][i] * dnno[j][i] - vnno[j][i]);
							vcorr = vnno[j][i] * vbiascorr;
							nno[j][i] -= learn * mnno[j][i] * mbiascorr / (sqrt(vcorr) + epsilon);
						}
						for (unsigned int j = 0; j < hidd; j++) {
							mnnh0hf[i][j] += beta1m * (dnnh0hf[i][j] - mnnh0hf[i][j]);
							vnnh0hf[i][j] += beta2m * (dnnh0hf[i][j] * dnnh0hf[i][j] - vnnh0hf[i][j]);
							vcorr = vnnh0hf[i][j] * vbiascorr;
							nnh0hf[i][j] -= learn * mnnh0hf[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnh0hi[i][j] += beta1m * (dnnh0hi[i][j] - mnnh0hi[i][j]);
							vnnh0hi[i][j] += beta2m * (dnnh0hi[i][j] * dnnh0hi[i][j] - vnnh0hi[i][j]);
							vcorr = vnnh0hi[i][j] * vbiascorr;
							nnh0hi[i][j] -= learn * mnnh0hi[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnh0hm[i][j] += beta1m * (dnnh0hm[i][j] - mnnh0hm[i][j]);
							vnnh0hm[i][j] += beta2m * (dnnh0hm[i][j] * dnnh0hm[i][j] - vnnh0hm[i][j]);
							vcorr = vnnh0hm[i][j] * vbiascorr;
							nnh0hm[i][j] -= learn * mnnh0hm[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnh0ho[i][j] += beta1m * (dnnh0ho[i][j] - mnnh0ho[i][j]);
							vnnh0ho[i][j] += beta2m * (dnnh0ho[i][j] * dnnh0ho[i][j] - vnnh0ho[i][j]);
							vcorr = vnnh0ho[i][j] * vbiascorr;
							nnh0ho[i][j] -= learn * mnnh0ho[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);

							mnnhhf[i][j] += beta1m * (dnnhhf[i][j] - mnnhhf[i][j]);
							vnnhhf[i][j] += beta2m * (dnnhhf[i][j] * dnnhhf[i][j] - vnnhhf[i][j]);
							vcorr = vnnhhf[i][j] * vbiascorr;
							nnhhf[i][j] -= learn * mnnhhf[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnhhi[i][j] += beta1m * (dnnhhi[i][j] - mnnhhi[i][j]);
							vnnhhi[i][j] += beta2m * (dnnhhi[i][j] * dnnhhi[i][j] - vnnhhi[i][j]);
							vcorr = vnnhhi[i][j] * vbiascorr;
							nnhhi[i][j] -= learn * mnnhhi[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnhhm[i][j] += beta1m * (dnnhhm[i][j] - mnnhhm[i][j]);
							vnnhhm[i][j] += beta2m * (dnnhhm[i][j] * dnnhhm[i][j] - vnnhhm[i][j]);
							vcorr = vnnhhm[i][j] * vbiascorr;
							nnhhm[i][j] -= learn * mnnhhm[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnhho[i][j] += beta1m * (dnnhho[i][j] - mnnhho[i][j]);
							vnnhho[i][j] += beta2m * (dnnhho[i][j] * dnnhho[i][j] - vnnhho[i][j]);
							vcorr = vnnhho[i][j] * vbiascorr;
							nnhho[i][j] -= learn * mnnhho[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);

							mnnhif[i][j] += beta1m * (dnnhif[i][j] - mnnhif[i][j]);
							vnnhif[i][j] += beta2m * (dnnhif[i][j] * dnnhif[i][j] - vnnhif[i][j]);
							vcorr = vnnhif[i][j] * vbiascorr;
							nnhif[i][j] -= learn * mnnhif[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnhii[i][j] += beta1m * (dnnhii[i][j] - mnnhii[i][j]);
							vnnhii[i][j] += beta2m * (dnnhii[i][j] * dnnhii[i][j] - vnnhii[i][j]);
							vcorr = vnnhii[i][j] * vbiascorr;
							nnhii[i][j] -= learn * mnnhii[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnhim[i][j] += beta1m * (dnnhim[i][j] - mnnhim[i][j]);
							vnnhim[i][j] += beta2m * (dnnhim[i][j] * dnnhim[i][j] - vnnhim[i][j]);
							vcorr = vnnhim[i][j] * vbiascorr;
							nnhim[i][j] -= learn * mnnhim[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnhio[i][j] += beta1m * (dnnhio[i][j] - mnnhio[i][j]);
							vnnhio[i][j] += beta2m * (dnnhio[i][j] * dnnhio[i][j] - vnnhio[i][j]);
							vcorr = vnnhio[i][j] * vbiascorr;
							nnhio[i][j] -= learn * mnnhio[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);

						}
						mh0fbias[i] += beta1m * (dh0fbias[i] - mh0fbias[i]);
						vh0fbias[i] += beta2m * (dh0fbias[i] * dh0fbias[i] - vh0fbias[i]);
						vcorr = vh0fbias[i] * vbiascorr;
						h0fbias[i] -= learn * mh0fbias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						mh0ibias[i] += beta1m * (dh0ibias[i] - mh0ibias[i]);
						vh0ibias[i] += beta2m * (dh0ibias[i] * dh0ibias[i] - vh0ibias[i]);
						vcorr = vh0ibias[i] * vbiascorr;
						h0ibias[i] -= learn * mh0ibias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						mh0mbias[i] += beta1m * (dh0mbias[i] - mh0mbias[i]);
						vh0mbias[i] += beta2m * (dh0mbias[i] * dh0mbias[i] - vh0mbias[i]);
						vcorr = vh0mbias[i] * vbiascorr;
						h0mbias[i] -= learn * mh0mbias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						mh0obias[i] += beta1m * (dh0obias[i] - mh0obias[i]);
						vh0obias[i] += beta2m * (dh0obias[i] * dh0obias[i] - vh0obias[i]);
						vcorr = vh0obias[i] * vbiascorr;
						h0obias[i] -= learn * mh0obias[i] * mbiascorr / (sqrt(vcorr) + epsilon);

						mhfbias[i] += beta1m * (dhfbias[i] - mhfbias[i]);
						vhfbias[i] += beta2m * (dhfbias[i] * dhfbias[i] - vhfbias[i]);
						vcorr = vhfbias[i] * vbiascorr;
						hfbias[i] -= learn * mhfbias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						mhibias[i] += beta1m * (dhibias[i] - mhibias[i]);
						vhibias[i] += beta2m * (dhibias[i] * dhibias[i] - vhibias[i]);
						vcorr = vhibias[i] * vbiascorr;
						hibias[i] -= learn * mhibias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						mhmbias[i] += beta1m * (dhmbias[i] - mhmbias[i]);
						vhmbias[i] += beta2m * (dhmbias[i] * dhmbias[i] - vhmbias[i]);
						vcorr = vhmbias[i] * vbiascorr;
						hmbias[i] -= learn * mhmbias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						mhobias[i] += beta1m * (dhobias[i] - mhobias[i]);
						vhobias[i] += beta2m * (dhobias[i] * dhobias[i] - vhobias[i]);
						vcorr = vhobias[i] * vbiascorr;
						hobias[i] -= learn * mhobias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
					}
					for (unsigned int i = 0; i < hidd; i++) {	//	just switched idim/hidd size of i/j loops
						mobias[i] += beta1m * (dobias[i] - mobias[i]);
						vobias[i] += beta2m * (dobias[i] * dobias[i] - vobias[i]);
						float vcorr = vobias[i] * vbiascorr;
						obias[i] -= learn * mobias[i] * mbiascorr / (sqrt(vcorr) + epsilon);
						for (unsigned int j = 0; j < idim; j++) {
							mnnh0if[i][j] += beta1m * (dnnh0if[i][j] - mnnh0if[i][j]);
							vnnh0if[i][j] += beta2m * (dnnh0if[i][j] * dnnh0if[i][j] - vnnh0if[i][j]);
							vcorr = vnnh0if[i][j] * vbiascorr;
							nnh0if[i][j] -= learn * mnnh0if[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnh0ii[i][j] += beta1m * (dnnh0ii[i][j] - mnnh0ii[i][j]);
							vnnh0ii[i][j] += beta2m * (dnnh0ii[i][j] * dnnh0ii[i][j] - vnnh0ii[i][j]);
							vcorr = vnnh0ii[i][j] * vbiascorr;
							nnh0ii[i][j] -= learn * mnnh0ii[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnh0im[i][j] += beta1m * (dnnh0im[i][j] - mnnh0im[i][j]);
							vnnh0im[i][j] += beta2m * (dnnh0im[i][j] * dnnh0im[i][j] - vnnh0im[i][j]);
							vcorr = vnnh0im[i][j] * vbiascorr;
							nnh0im[i][j] -= learn * mnnh0im[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
							mnnh0io[i][j] += beta1m * (dnnh0io[i][j] - mnnh0io[i][j]);
							vnnh0io[i][j] += beta2m * (dnnh0io[i][j] * dnnh0io[i][j] - vnnh0io[i][j]);
							vcorr = vnnh0io[i][j] * vbiascorr;
							nnh0io[i][j] -= learn * mnnh0io[i][j] * mbiascorr / (sqrt(vcorr) + epsilon);
					}	}
				}
				else {
					for (int i = 0; i < idim; i++) {	//	apply learning no ADAM ('gradient descent' funny name)
						for (int j = 0; j < hidd; j++) {
							nno[i][j] -= dnno[i][j] * learn;			//	all five of these need to be swapped in lstm
							nnh0if[j][i] -= dnnh0if[j][i] * learn;
							nnh0ii[j][i] -= dnnh0ii[j][i] * learn;
							nnh0im[j][i] -= dnnh0im[j][i] * learn;
							nnh0io[j][i] -= dnnh0io[j][i] * learn;
						}
						obias[i] -= dobias[i] * learn;
					}
					for (int i = 0; i < hidd; i++) {
						h0fbias[i] -= dh0fbias[i] * learn;
						h0ibias[i] -= dh0ibias[i] * learn;
						h0mbias[i] -= dh0mbias[i] * learn;
						h0obias[i] -= dh0obias[i] * learn;
						hfbias[i] -= dhfbias[i] * learn;
						hibias[i] -= dhibias[i] * learn;
						hmbias[i] -= dhmbias[i] * learn;
						hobias[i] -= dhobias[i] * learn;
						for (int j = 0; j < hidd; j++) {
							nnh0hf[i][j] -= dnnh0hf[i][j] * learn;
							nnh0hi[i][j] -= dnnh0hi[i][j] * learn;
							nnh0hm[i][j] -= dnnh0hm[i][j] * learn;
							nnh0ho[i][j] -= dnnh0ho[i][j] * learn;
							nnhhf[i][j] -= dnnhhf[i][j] * learn;
							nnhhi[i][j] -= dnnhhi[i][j] * learn;
							nnhhm[i][j] -= dnnhhm[i][j] * learn;
							nnhho[i][j] -= dnnhho[i][j] * learn;
							nnhif[i][j] -= dnnhif[i][j] * learn;
							nnhii[i][j] -= dnnhii[i][j] * learn;
							nnhim[i][j] -= dnnhim[i][j] * learn;
							nnhio[i][j] -= dnnhio[i][j] * learn;
					}	}
				}

			}
			tests++;
			sb = st;
			
			if (!(tests & 255)) {
				if (stop) {
					tests = wavsamples;	thismany = 10;
				}
				InvalidateRgn(hWnd, 0, 0);	UpdateWindow(hWnd);
				MSG tmsg;
				while (PeekMessage(&tmsg, hWnd, 0, 0, PM_REMOVE)) { TranslateMessage(&tmsg); DispatchMessage(&tmsg); }
			}
		}

		thismany++;
	}
	action = 0;
	stop = 0;
	if (audition) audition = 0;
}





void FillAudioBuffer(PBYTE pBuffer) {
	for (int buffercount = 0; buffercount < OUT_BUFFER_SIZE; buffercount += 4) {
		float outl = 0, outr = 0;
		if (audition) {
			outl = outr = out1[(p >> 2)];
			p++;	p &= BUFFMASK;
		}

		int aui = (int)outl;	aui = min(max(-32767, aui), 32767);
		int auj = (int)outr;	auj = min(max(-32767, auj), 32767);
		pBuffer[buffercount] = aui;		pBuffer[buffercount + 1] = aui >> 8;
		pBuffer[buffercount + 2] = auj;	pBuffer[buffercount + 3] = auj >> 8;
	}
};
