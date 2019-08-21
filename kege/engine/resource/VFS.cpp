//
//  VFS.cpp
//  KEGE
//
//  Created by Kenneth Esdaile on 5/27/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//
#include "xml.hpp"
#include "Logger.hpp"
#include "VFS.hpp"
namespace kege{

    void DropError(int code, const ds::string& msg)
    {
        switch (code)
        {
            case 1:
                kege::Logger::log["error"].Msg("unale to un-virtualize virpath for %s\n", msg.c_str());
                break;
                
            case 2:
                kege::Logger::log["error"].Msg("unale to un-virtualize filepath for %s\n", msg.c_str());
                break;
                
            default:
                break;
        }
    }
    
    void ParseRouteNames(ds::string& pid, ds::string& fname, const ds::string& filename)
    {
        const char * str = filename.c_str();
        const char * s   = str;
        
        while ((*s == '~' || *s == '/') && *s != 0) s++;
        str = s;
        while (*s != '/' && *s != 0) s++;
        pid.copy(str, s-str);
        s++;
        fname = s;
    }
    
    ds::string kege::VFS::File::GetFileData()
    {
        FILE * file = fopen(filename.c_str(), "r");
        if (!file)
        {
            fprintf(stderr,"error: LoadXML(%s) file not found.\n",filename.c_str());
            return ds::string();
        }
        
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);
        
        if (size == 0)
        {
            return ds::string();
        }
        
        char* data = new char[size+1];
        fread(data, size, sizeof(char), file);
        data[size] = '\0';
        
        return ds::string(data, size);
    }
    
    VFS::File kege::VFS::GetFile(const ds::string& vid, const ds::string& fname)
    {
        std::map<keytype, ds::dlist<VirPath>>::const_iterator v = virpaths.find(vid.hash());
        if (v != virpaths.end())
        {
            for (ds::dlist<VirPath>::iterator f=v->second.begin(); f!=nullptr; f++)
            {
                const VirPath* link = &f.element();
                ds::string real_filename = GetFilePath(link) + "/" + fname;
                
                FILE* file = fopen(real_filename.c_str(), "r");
                if (file == nullptr) continue;
                
                return VFS::File(file, real_filename);
            }
        }
        return VFS::File();
    }
    
    ds::string kege::VFS::GetFilePath(const VirPath* link)
    {
        const FilePath* vir = GetFilePath(link->vid);
        if (vir == nullptr)
        {
            DropError(1, "link->vid path does not exist");
            return ds::string();
        }
        const FilePath* dir = GetFilePath(link->pid);
        if (dir == nullptr)
        {
            DropError(2, "link->pid path does not exist");
            return ds::string();
        }
        
        return dir->path + vir->path.c_str();
    }
    
    const kege::VFS::FileExt* kege::VFS::GetFileExtLink(const ds::string& ext_id)const
    {
        keytype k = ext_id.hash();
        std::map<keytype, ds::dlist<FileExt>>::const_iterator m = fileexts.find(k);
        if (m != fileexts.end())
        {
            for (ds::dlist<FileExt>::iterator f=m->second.begin(); f!=nullptr; f++)
            {
                if (f.element().id == ext_id)
                {
                    return &f.element();
                }
            }
        }
        return nullptr;
    }
    const kege::VFS::VirPath* kege::VFS::GetVirtualLink(const ds::string& vir_id)const
    {
        keytype k = vir_id.hash();
        std::map<keytype, ds::dlist<VirPath>>::const_iterator m = virpaths.find(k);
        if (m != virpaths.end())
        {
            for (ds::dlist<VirPath>::iterator f=m->second.begin(); f!=nullptr; f++)
            {
                if (f.element().id == vir_id)
                {
                    return &f.element();
                }
            }
        }
        return nullptr;
    }
    const kege::VFS::FilePath* kege::VFS::GetFilePath(const ds::string& path_id)const
    {
        keytype k = path_id.hash();
        std::map<keytype, ds::dlist<FilePath>>::const_iterator m = filepaths.find(k);
        if (m != filepaths.end())
        {
            for (ds::dlist<FilePath>::iterator f=m->second.begin(); f!=nullptr; f++)
            {
                if (f.element().id == path_id)
                {
                    return &f.element();
                }
            }
        }
        return nullptr;
    }
    void kege::VFS::FileExtLink(const ds::string& id, const ds::string& pid, char link_type)
    {
        keytype k = id.hash();
        std::map<keytype, ds::dlist<FileExt>>::iterator m = fileexts.find(k);
        if (m == fileexts.end())
        {
            FileExt& ext = fileexts[k].push_back();
            ext.link = link_type;
            ext.id = id;
            ext.pid = pid;
            return;
        }
        FileExt& ext = m->second.push_back();
        ext.link = link_type;
        ext.id = id;
        ext.pid = pid;
    }
    
    void kege::VFS::VirtualLink(const ds::string& id, const ds::string& dir_id, const ds::string& vir_id)
    {
        keytype k = id.hash();
        std::map<keytype, ds::dlist<VirPath>>::iterator m = virpaths.find(k);
        if (m == virpaths.end())
        {
            VirPath& vir = virpaths[k].push_back();
            vir.pid = dir_id;
            vir.vid = vir_id;
            vir.id = id;
            return;
        }
        VirPath& vir = m->second.push_back();
        vir.pid = dir_id;
        vir.vid = vir_id;
        vir.id = id;
    }
    
    void kege::VFS::AddFilePath(const ds::string& id, const ds::string& path)
    {
        keytype k = id.hash();
        std::map<keytype, ds::dlist<FilePath>>::iterator m = filepaths.find(k);
        if (m == filepaths.end())
        {
            FilePath& dir = filepaths[k].push_back();
            dir.path = path;
            dir.id = id;
            return;
        }
        FilePath& dir = m->second.push_back();
        dir.path = path;
        dir.id = id;
    }
    
    FILE* kege::VFS::GetFile(const ds::string& filename)
    {
        // if fname is empty return empty string, nothing can be done.
        if ( filename.empty() ) return nullptr;
        
        // if the first character of the string is ~ then its a virtual-file access
        // example : filename is type --> "~/models/warrior.obj"
        if (filename[0] == '~')
        {
            ds::string pid;
            ds::string fname;
            ParseRouteNames(pid, fname, filename);
            return GetFile(pid, fname).file;
        }
        
        // if the first character of the string is not / then it is just the name of a file
        // example : filename is type --> "warrior.obj"
        if (filename[0] != '/')
        {
            const FileExt* ext = GetFileExtLink( filename.parse_fext() );
            if (ext == nullptr) return nullptr;
            
            if (ext->link == 'v')
            {
                return GetFile(ext->pid, filename).file;
            }
            else if (ext->link == 'r')
            {
                const FilePath* dir = GetFilePath(ext->pid);
                if (dir == nullptr)
                {
                    DropError(2, filename);
                    return nullptr;
                }
                ds::string fname = dir->path + filename;
                return fopen(fname.c_str(), "r");
            }
        }
        return fopen(filename.c_str(), "r");
    }
    
    VFS::File  kege::VFS::OpenFile(ds::string const& filename)
    {
        // if fname is empty return empty string, nothing can be done.
        if (filename.empty()) return VFS::File();
        
        // if the first character of the string is ~ then its a virtual-file access
        // example : filename is type --> "~/models/warrior.obj"
        if (filename[0] == '~')
        {
            ds::string pid;
            ds::string fname;
            ParseRouteNames(pid, fname, filename);
            return GetFile(pid, fname);
        }
        
        // if the first character of the string is not / then it is just the name of a file
        // example : filename is type --> "warrior.obj"
        if (filename[0] != '/')
        {
            const FileExt* ext = GetFileExtLink( filename.parse_fext() );
            if (ext == nullptr) return VFS::File();
            
            if (ext->link == 'v')
            {
                return GetFile(ext->pid, filename);
            }
            else if (ext->link == 'r')
            {
                const FilePath* dir = GetFilePath(ext->pid);
                if (dir == nullptr)
                {
                    DropError(2, filename);
                    return VFS::File();
                }
                ds::string fname = dir->path + filename;
                return VFS::File(fopen(fname.c_str(), "r"), fname);
            }
        }
        return VFS::File(fopen(filename.c_str(), "r"), filename);
    }
    
    ds::string kege::VFS::GetFilename(ds::string const& filename)
    {
        VFS::File f = OpenFile(filename);
        if (f.file != nullptr)
        {
            return f.filename;
        }
        return ds::string();
    }
    
    bool kege::VFS::Save(const kege::ds::string& filename)
    {
        FILE* file = fopen(filename.c_str(), "w");
        if (file == nullptr) return false;
        
        std::map<keytype, ds::dlist<FilePath>>::const_iterator m;
        
        fprintf(file, "<VFS>\n");
        m = filepaths.begin();
        for (; m!=filepaths.end(); m++)
        {
            for (ds::dlist<FilePath>::iterator f=m->second.begin(); f!=nullptr; f++)
            {
                FilePath& a = f.element();
                fprintf(file, "  <filepath id=\"%s\">%s</filepath>\n", a.id.c_str(),a.path.c_str());
            }
        }
        
        std::map<keytype, ds::dlist<VirPath>>::const_iterator k;
        k = virpaths.begin();
        for (; k!=virpaths.end(); k++)
        {
            for (ds::dlist<VirPath>::iterator f=k->second.begin(); f!=nullptr; f++)
            {
                VirPath& a = f.element();
                fprintf(file, "  <virpath id=\"%s\" pid=\"%s\" vid=\"%s\"/>\n", a.id.c_str(), a.pid.c_str(), a.vid.c_str());
            }
        }
        
        std::map<keytype, ds::dlist<FileExt>>::const_iterator n;
        
        n = fileexts.begin();
        for (; n!=fileexts.end(); n++)
        {
            for (ds::dlist<FileExt>::iterator f=n->second.begin(); f!=nullptr; f++)
            {
                FileExt& a = f.element();
                if (*a.pid.c_str() == 'v')
                {
                    fprintf(file, "  <fileext  type=\"%c\" id=\"%s\" vid=\"%s\"/>\n", a.link, a.id.c_str(), a.pid.c_str());
                }
                else
                {
                    fprintf(file, "  <fileext  type=\"%c\" id=\"%s\" pid=\"%s\"/>\n", a.link, a.id.c_str(), a.pid.c_str());
                }
            }
        }
        fprintf(file, "</VFS>");
        return true;
    }
    
    bool kege::VFS::Load(const kege::ds::string& filename)
    {
        kege::XML xml;
        if (!xml.Load(filename)) return false;
        
        kege::XML* vfs = xml.GetChild("VFS");
        if (vfs == nullptr) return false;
        
        kege::XML::attrib* pid  = nullptr;
        kege::XML::attrib* vid  = nullptr;
        kege::XML::attrib* id   = nullptr;
        kege::XML::attrib* type = nullptr;
        for (kege::XML::list::iterator i=vfs->Begin(); i!=nullptr; i++)
        {
            if (i->GetName() == "filepath")
            {
                AddFilePath(i->GetAttr("id")->value, i->GetText());
            }
            else if (i->GetName() == "virpath")
            {
                id  = i->GetAttr("id");
                pid = i->GetAttr("pid");
                vid = i->GetAttr("vid");
                if (id != nullptr && pid != nullptr && vid != nullptr)
                {
                    VirtualLink(id->value, pid->value, vid->value);
                }
            }
            else if (i->GetName() == "fileext")
            {
                type = i->GetAttr("type");
                id   = i->GetAttr("id");
                if (type == nullptr) continue;
                
                if (*type->value.c_str() == 'v')
                {
                    vid = i->GetAttr("vid");
                    if (id != nullptr && vid != nullptr)
                    {
                        FileExtLink(id->value, vid->value, *type->value.c_str());
                    }
                }
                else
                {
                    pid = i->GetAttr("pid");
                    if (id != nullptr && pid != nullptr)
                    {
                        FileExtLink(id->value, pid->value, *type->value.c_str());
                    }
                }
            }
        }
        return true;
    }
    
    bool kege::VFS::FileIsValid(const kege::ds::string& filename)
    {
        FILE* file = fopen(filename.c_str(), "r");
        if (file == nullptr) return false;
        fclose(file);
        file = nullptr;
        return true;
    }
    
    kege::VFS::VFS(ds::string const& filename)
    {
        Load(filename);
    }
    
    bool kege::VFS::IsLoaded()
    {
        return filepaths.size() != 0 || virpaths.size() != 0;
    }
    
    void kege::VFS::Clear()
    {
        filepaths.clear();
        fileexts.clear();
        virpaths.clear();
    }
    
    kege::VFS::~ VFS()
    {
        Clear();
    }
    
    kege::VFS::VFS()
    {}
}




//File File::GetFileFromPath(const kege::ds::string& fname)
//{
//    if (filename.empty())
//    {
//        return File(fname);
//    }
//    ds::string str = filename;
//    char *f = &str[str.length()-1];
//    char *e, *s = str.getdata();
//    while (*f!=0) f++;
//    f--;
//    e=f;
//    for (const char* a=fname.c_str(); *a!=0; a++)
//    {
//        if (a[0] != '.' && a[1] != '.')
//        {
//            if (f[1] == '/')
//                f+=2;
//            *f = 0;
//            str.setlength(str.length() - (e-f+1));
//            str.overwrtie(str.length(), strlen(a), a);
//            return File(str);
//        }
//        a+=2;
//        
//        if (*f == '/') f--;
//        while (*f != '/') f--;
//        if (f - s != 0) f--;
//        else
//        {
//            return kege::File(a);
//        }
//    }
//    return kege::File();
//}
