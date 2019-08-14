//
//  VFS.hpp
//  KEGE
//
//  Created by Kenneth Esdaile on 5/27/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef VFS_hpp
#define VFS_hpp

#ifndef SafeDelete
#define SafeDelete(p){ if(p){delete p; p=nullptr;} }
#endif

#ifndef SafeDeleteArray
#define SafeDeleteArray(p){ if(p){delete []p; p=nullptr;} }
#endif

#include <map>
#include <vector>
#include "string.hpp"
#include "dlist.hpp"
#include "File.hpp"
namespace kege{
    
    class VFS
    {
        struct FilePath
        {
            kege::ds::string path;
            kege::ds::string id;
        };
        struct VirPath
        {
            kege::ds::string vid;
            kege::ds::string pid;
            kege::ds::string id;
        };
        struct FileExt
        {
            kege::ds::string pid;
            kege::ds::string id;
            char link;
        };
        
    public:
        
        class File
        {
        public:
            ds::string GetFileData();
            File(FILE* f, const ds::string& fn)
            :   filename(fn)
            ,   file(f)
            {}
            File()
            :   file(nullptr)
            {}
            ~ File()
            {
                if (file != nullptr)
                {
                    fclose(file);
                    file = nullptr;
                }
            }
            ds::string filename;
            FILE* file;
        };
        
    protected:
        
        VFS::File  GetFile(const ds::string& vid, const ds::string& fname);
        ds::string GetFilePath(const VirPath* link);
        
        typedef unsigned long keytype;
        
    public:
        
        void VirtualLink(const ds::string& id, const ds::string& dir_id, const ds::string& vir_id);
        void FileExtLink(const ds::string& id, const ds::string& p_id, char link_type);
        void AddFilePath(const ds::string& id, const ds::string& path);
        
        const FileExt*  GetFileExtLink(const ds::string& ext_id)const;
        const VirPath*  GetVirtualLink(const ds::string& vir_id)const;
        const FilePath* GetFilePath(const ds::string& path_id)const;
        
        ds::string GetFilename(const ds::string& filename);
        VFS::File  OpenFile(const ds::string& filename);
        FILE* GetFile(const ds::string& filename);
        
        bool Save(const kege::ds::string& fname);
        bool Load(const kege::ds::string& fname);
        
        bool IsLoaded();
        void Clear();
        
        static kege::VFS& GetInstance()
        {
            static kege::VFS instance;
            return instance;
        }
        
        VFS(ds::string const& filename);
        virtual ~ VFS();
        VFS();
        
        
    private:
        
        bool FileIsValid(const kege::ds::string& fname);
        VFS(kege::VFS const&);
        
        std::map<keytype, ds::dlist<FilePath>> filepaths;
        std::map<keytype, ds::dlist<VirPath>> virpaths;
        std::map<keytype, ds::dlist<FileExt>> fileexts;
    };
    
}
#endif /* vsf_hpp */


