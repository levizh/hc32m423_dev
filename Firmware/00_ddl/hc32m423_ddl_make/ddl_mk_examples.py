# coding=gb2312

import config as DDL
import config
import os
import shutil
import re
import utils

TEMPLATE_SRC = os.path.join( DDL.CUR_DIR, 'template_prj\\')


g_driver_list = []
g_midware_list = []
g_bsp_list = []

def copyFiles(sourceDir,  targetDir): 
    for file in os.listdir(sourceDir): 
        sourceFile = os.path.join(sourceDir,  file) 
        targetFile = os.path.join(targetDir,  file) 
        if os.path.isfile(sourceFile): 
            if not os.path.exists(targetDir):  
                os.makedirs(targetDir)  
            if not os.path.exists(targetFile) or(os.path.exists(targetFile) and (os.path.getsize(targetFile) != os.path.getsize(sourceFile))):
                    open(targetFile, "wb").write(open(sourceFile, "rb").read()) 
        if os.path.isdir(sourceFile): 
            First_Directory = False 
            copyFiles(sourceFile, targetFile)



##################################################################
def make_iar_project(rootdir,dir,prj,file,depth):
    #load eww,ewp file
    ewd_filename = ''
    eww_filename = ''
    ewp_filename = ''
    sample_prj_name1 = prj +'_'+ file
    sample_prj_name = file

    print('make iar proj -> ' + sample_prj_name1)

    #make the ..\..\
    back_path = ''
    for i in range(depth):
        back_path += "..\\\\"
    
    dir = dir.replace('\\source','',1)
    src = os.path.join(dir,'EWARM')

    #rename eww file
    name1 = os.path.join(src,'ddl_template.eww')
    eww_filename = os.path.join(src,file+'.eww') #full path
    os.rename(name1,eww_filename)

    #modify eww
    name2 = os.path.join(src,eww_filename)
    f1 = open(name2)
    buff_out = f1.read()
    f1.close()
    f1 = open(name2,'wb')
    buff_out = re.sub('{PERIPHERAL}',prj,buff_out)
    buff_out = re.sub('{FEATURE}',file,buff_out)
    f1.write(buff_out.encode())
    f1.close()

    #rename ewd file
    name1 = os.path.join(src,'ddl_template.ewd')
    ewd_filename = sample_prj_name +'.ewd'
    name2 = os.path.join(src,ewd_filename)
    os.rename(name1,name2)

    #modify ewd file
    name2 = os.path.join(src,ewd_filename)
    f1 = open(name2)
    buff_out = f1.read()
    f1.close()
    f1 = open(name2,'w')
    buff_out = re.sub('{SAMPLE_DEPTH}',back_path,buff_out)
    f1.write(buff_out)
    f1.close()

    #####################ewp file#################################
    #rename ewp file
    name1 = os.path.join(src,'ddl_template.ewp')
    ewp_filename = sample_prj_name +'.ewp'
    name2 = os.path.join(src,ewp_filename) 
    os.rename(name1,name2)

    #modify ewp
    name2 = os.path.join(src,ewp_filename)
    f1 = open(name2)
    buff_out = f1.read()
    f1.close()

    #eww parse c file in source group
    src1_file = ''
    src1_flag = 0
    src1_list = os.listdir(dir + os.sep +'source')
    for src1 in src1_list:
        if (src1.split('.')[1] == 'c') & (src1.split('.')[0] != 'main') :
            src1_flag += 1
            if prj != file:
                src1_file += '<file>' + '<name>$PROJ_DIR$\\\\' + back_path + 'example\\\\' + prj + '\\\\' + file \
                        + '\\\\source\\\\' + src1 + '</name>' + '</file>'
            else:
                src1_file += '<file>' + '<name>$PROJ_DIR$\\\\' + back_path + 'example\\\\' + file \
                             + '\\\\source\\\\' + src1 + '</name>' + '</file>'
    if src1_flag :
        buff_out = re.sub('<custom>{PROJ_SRC}</custom>', src1_file, buff_out)

    #eww parse driver c file
    c_src_file = ''
    
    dst_list = utils.find_inc(dir+ os.sep+'source'+os.sep + 'ddl_config.h')
    for dl in dst_list:
        dl = dl.lower()
        dl_series = DDL.SERIES.lower()
        dl =  dl_series + '_'+ dl
        for sl in g_driver_list:
                #if(dl == sl and 'gpio' != dl and 'clk' != dl and 'ddl' != dl):
                if(dl == sl and 'ddl' != dl):
                    c_src_file += '    <file>' + os.linesep + \
                    '      <name>$PROJ_DIR$\\\\' + back_path + \
                    'driver\\\\src\\\\' + dl + \
                    '.c</name>' + os.linesep + \
                    '    </file>' + os.linesep
                    break
    ###############################


    # eww parse midware c file
    mid_inc_file = ''
    mid_src_file = ''
    mid_flag = 0
    #find midware group
    mw_dst_list = utils.find_mid(dir + os.sep + 'source' + os.sep + 'ddl_config.h')

    for mdl in mw_dst_list:
        mdl = mdl.split('_')[0]
        mdl = mdl.lower()
        for msl in g_midware_list:
            if(msl == mdl):
                mid_flag += 1
                #add midware.h
                mid_inc_file += '<state>$PROJ_DIR$\\\\' + back_path + \
                'midware\\\\' + mdl +'\\\\inc' + '</state>' + os.linesep
                #add midware.c
                mid_src_list = os.listdir(DDL.DDL_MIDWARE_DIR + os.sep + mdl + os.sep + 'src')
                mid_src_file += '  <group>' + os.linesep + '    <name>' + mdl + '</name>' + os.linesep
                for mid_src in mid_src_list:
                    mid_src_file += '    <file>' + os.linesep + \
                    '      <name>$PROJ_DIR$\\\\' + back_path + \
                    'midware\\\\' + mdl + '\\\\src\\\\' + mid_src + \
                    '</name>' + os.linesep + \
                    '    </file>' + os.linesep
                mid_src_file += '</group>' + os.linesep
    if(mid_flag > 0):
        mid_group_head = '<group>' + os.linesep + '    <name>midware</name>' + os.linesep
        mid_group_tail = '</group>' + os.linesep

        buff_out = re.sub('<custom>{PROJ_MIDWARE_GRP_H}</custom>', mid_group_head, buff_out)
        buff_out = re.sub('<custom>{PROJ_MIDWARE_GRP_T}</custom>', mid_group_tail, buff_out)
        buff_out = re.sub('<custom>{PROJ_MIDWARE_SRC}</custom>', mid_src_file, buff_out)
        buff_out = re.sub('<custom>{PROJ_MIDWARE_INC}</custom>', mid_inc_file, buff_out)

    #eww pash bsp c file
    bsp_inc_file = ''
    bsp_src_file = ''
    bsp_src = ''
    bsp_flag = 0
    #find bsp group
    bsp_dst_list = utils.find_bsp(dir + os.sep + 'source' + os.sep + 'ddl_config.h')
    for bsp in bsp_dst_list:
        bsp = bsp.lower()
        if bsp.split('_')[-1] == 'enable':
            bsp = bsp.split('_enable')[0]
        for bs in g_bsp_list:
            if bs == bsp:
                bsp_flag += 1
                if (bsp.split('_')[0] == 'ev') | (bsp.split('_')[0] == 'ms'):
                    # add bsp.h
                    bsp_inc_file += '<state>$PROJ_DIR$\\\\' + back_path + \
                    'bsp\\\\' + bsp + '</state>'+os.linesep
                    # add bsp.c
                    bsp_src_file += '  <group>' + os.linesep + '    <name>' + bsp + '</name>' + os.linesep

                    bsp_src_file += '<file>' + os.linesep + '<name>$PROJ_DIR$\\\\' + back_path + \
                    'bsp\\\\' + bsp + '\\\\' + bsp + '.c' + '</name>' + os.linesep + '</file>' + os.linesep + \
                    '<custom>{bsp_src}</custom>'
                    bsp_src_file += '</group>' + os.linesep

                else:
                    # add bsp.h
                    bsp_inc_file += '<state>$PROJ_DIR$\\\\' + back_path + \
                    'bsp\\\\' + 'components\\\\' + bsp + '</state>'+os.linesep

                    # add bsp.c
                    bsp_src_file += '  <group>' + os.linesep + '    <name>' + bsp + '</name>' + os.linesep

                    bsp_src_file += '<file>' + os.linesep + '<name>$PROJ_DIR$\\\\' + back_path + \
                    'bsp\\\\' + 'components\\\\' + bsp + '\\\\' + bsp+'.c' + '</name>' + os.linesep + '</file>' + os.linesep
                    bsp_src_file += '</group>' + os.linesep

                if (bsp_flag > 1) & ((bsp_dst_list[0].split('_')[0] == 'EV') | (bsp_dst_list[0].split('_')[0] == 'MS')):
                    # add bsp.c
                    bsp_src_name = bsp_dst_list[0].lower() + '_' + bsp

                    bsp_src += '<file>' + os.linesep + '<name>$PROJ_DIR$\\\\' + back_path + \
                               'bsp\\\\' + bsp_dst_list[0].lower() + '\\\\' + bsp_src_name + '.c' + \
                               '</name>' + os.linesep + '</file>' + os.linesep
    if (bsp_flag > 0):
        bsp_group_head = '<group>' + os.linesep + '<name>bsp</name>' + os.linesep
        bsp_group_tail = '</group>' + os.linesep

        buff_out = re.sub('<custom>{PROJ_BSP_GRP_H}</custom>', bsp_group_head, buff_out)
        buff_out = re.sub('<custom>{PROJ_BSP_GRP_T}</custom>', bsp_group_tail, buff_out)

        buff_out = re.sub('<custom>{PROJ_BSP_SRC}</custom>', bsp_src_file, buff_out)
        buff_out = re.sub('<custom>{PROJ_BSP_INC}</custom>', bsp_inc_file, buff_out)
        buff_out = re.sub('<custom>{bsp_src}</custom>', bsp_src, buff_out)

    ###############################
    ###  ETH & USB Project make
    cnt = 0
    cnt1 = 0
    flag = 0
    c_src_file1 = ''
    h_inc_file1 = ''
    SpcPoj_list = config.Prj_list
    Example_list = utils.find_example(DDL.CUR_DIR + os.sep + 'config.py')
    for poj in SpcPoj_list:
        if prj == poj:
            for exam in Example_list:
                if exam == file:
                    example_src_list = example_dict[prj + '_' + exam + '_source']
                    example_inc_list = example_dict[prj + '_' + exam + '_header']
                    for exa_src in example_src_list:
                        if exa_src.split('\\\\')[0] == 'driver':
                            c_src_file += '    <file>' + os.linesep + \
                                          '      <name>$PROJ_DIR$\\\\' + back_path + \
                                          exa_src + '</name>' + os.linesep + \
                                          '    </file>' + os.linesep
                            continue
                        num = len(exa_src.split('\\\\'))
                        if num == 1:
                            num = len(example_src_list[cnt - 1].split('\\\\')) + 1
                        cnt += 1
                        flag1 = 0
                        for l in range(num):
                            if ('..' in exa_src) & ('....' not in exa_src):
                                exa_src = example_src_list[cnt - 2] + '\\\\' + example_src_list[cnt -1]
                                exa_src = exa_src.replace('..','')
                                flag1 = 1
                                cnt1 += 1
                            if '....' in exa_src:
                                if '\\\\' not in example_src_list[cnt - 2]:
                                    exa_src = example_src_list[cnt - 3].replace(example_src_list[cnt - 3].split('\\\\')[-1], '') + '\\\\' + example_src_list[cnt - 1]
                                else:
                                    exa_src = example_src_list[cnt - 2].replace(example_src_list[cnt - 2].split('\\\\')[-1],'') + '\\\\' + example_src_list[cnt -1]
                                exa_src = exa_src.replace('....','')
                                flag1 = 1
                                cnt1 += 1
                            if (flag1 == 0) & (flag == 1) & (exa_src.split('\\\\')[l] != 'ethernet.c'):
                                for a in range(cnt1 + 1):
                                    c_src_file1 += '</group>' + os.linesep
                                cnt1 = 0
                                flag = 0
                            if exa_src.split('\\\\')[l] in c_src_file1:
                                if exa_src.split('\\\\')[l] == 'netif':
                                    c_src_file1 += '<group>' + os.linesep + '<name>' + exa_src.split('\\\\')[l] + '</name>' + os.linesep
                                if exa_src.split('\\\\')[l] == 'msc':
                                    c_src_file1 += '<group>' + os.linesep + '<name>' + exa_src.split('\\\\')[l] + '</name>' + os.linesep
                                continue

                            if '.c' in exa_src.split('\\\\')[l]:
                                continue
                            else:
                                if exa_src.split('\\\\')[l] in c_src_file1:
                                    continue
                                c_src_file1 += '<group>' + os.linesep + '<name>' + exa_src.split('\\\\')[l] + '</name>' + os.linesep

                        if os.path.isdir(DDL.DDL_DIR + '\\\\' + exa_src):
                            C_list = os.listdir(DDL.DDL_DIR + '\\\\' + exa_src)
                            for c_list in C_list:
                                if os.path.isdir(DDL.DDL_DIR + '\\\\' + exa_src + '\\\\' + c_list):
                                    continue
                                if c_list.split('.')[1] == 'c':
                                    c_src_file1 += '<file>' + os.linesep + '<name>$PROJ_DIR$\\\\' + back_path + \
                                                exa_src + '\\\\' + c_list + '</name>' + os.linesep + '</file>' + os.linesep
                        else:
                            c_src_file1 += '<file>' + os.linesep + '<name>$PROJ_DIR$\\\\' + back_path + \
                                           exa_src + '</name>' + os.linesep + '</file>' + os.linesep
                        flag = 1
                    for a in range(cnt1 + 1):
                        c_src_file1 += '</group>' + os.linesep
                    if prj == 'eth':
                        for a in range(3):
                            c_src_file1 += '</group>' + os.linesep
                    if prj == 'usb':
                        for a in range(3):
                            c_src_file1 += '</group>' + os.linesep

                    for exa_inc in example_inc_list:
                        h_inc_file1 += '<state>$PROJ_DIR$\\\\' + back_path + exa_inc  + '</state>'+os.linesep
                    buff_out = re.sub('<custom>{PROJ_MIDWARE_SRC}</custom>', c_src_file1, buff_out)

                    buff_out = re.sub('<custom>{PROJ_MIDWARE_INC}</custom>', h_inc_file1, buff_out)

    ################
    f1 = open(name2,'wb')

    buff_out = re.sub('{PROJ_DRIVER_SRC}',c_src_file,buff_out)
    buff_out = re.sub('{SAMPLE_DEPTH}',back_path,buff_out)
    buff_out = re.sub('{FEATURE}',file,buff_out)


    f1.write(buff_out.encode())
    f1.close()            


    #rename jlink config file
    name1 = src + os.sep + 'settings' + os.sep + 'ddl_template.jlink'
    name2 = src + os.sep + 'settings' + os.sep + sample_prj_name+'_Release.jlink'
    shutil.copy(name1,name2)
    name2 = src + os.sep + 'settings' + os.sep + sample_prj_name+'_Debug.jlink'    
    os.rename(name1,name2)

    #rename dni config file
    name1 = src + os.sep + 'settings' + os.sep + 'ddl_template.dni'
    name2 = src + os.sep + 'settings' + os.sep + sample_prj_name + '.dni'
    os.rename(name1, name2)

    #modify dni config file
    name1 = src + os.sep + 'settings' + os.sep + sample_prj_name + '.dni'
    f1 = open(name1)
    buff_out = f1.read()
    f1.close()
    f1 = open(name1, 'w')
    buff_out = re.sub('{SAMPLE_DEPTH}', back_path, buff_out)
    f1.write(buff_out)
    f1.close()

    #modify flashloader/board
    src2 = os.path.join(src,'flashloader')
    temp = 'Flash' + DDL.SERIES.upper() + '.flash'
    name1 = os.path.join(src2,temp)
    f1 = open(name1)
    buff_out = f1.read()
    f1.close()
    f1 = open(name1,'w')
    buff_out = re.sub('{SAMPLE_DEPTH}',back_path,buff_out)
    f1.write(buff_out)
    f1.close()
    


#make keil project
def make_keil_project(rootdir,dir,prj,file,depth):
    sample_prj_name = prj +'_'+ file
    
    print ('make keil proj -> ' + sample_prj_name)


    dir = dir.replace('\\source','',1)
    src = os.path.join(dir,'MDK')

    #make the ..\..\
    back_path = ''
    sfr_path = ''
    for i in range(depth):
        back_path += "..\\\\"
        sfr_path += "/.."

    ####################################
    #rename uvprojx
    name1 = os.path.join(src,'ddl_template.uvprojx')
    name2 = os.path.join(src,file + '.uvprojx')
    os.rename(name1,name2)

    f1 = open(name2)
    buff_out = f1.read()
    f1.close()
    f1 = open(name2,'wb')

    #modify uvprojx

    #eww parse c file in source group
    src1_file = ''
    src1_flag = 0
    src1_list = os.listdir(dir + os.sep +'source')
    for src1 in src1_list:
        if (src1.split('.')[1] == 'c') & (src1.split('.')[0] != 'main') :
            src1_flag += 1
            if prj != file:
                src1_file += '<File>' + os.linesep + \
                        '<FileName>' + src1 + '</FileName>' + os.linesep + \
                        '<FileType>1</FileType>' + \
                        '<FilePath>' + back_path + 'example\\\\' + prj + '\\\\' + file + \
                         '\\\\source\\\\' + src1  + '</FilePath>' + \
                        '</File>' + os.linesep
            else:
                src1_file += '<File>' + os.linesep + \
                             '<FileName>' + src1 + '</FileName>' + os.linesep + \
                             '<FileType>1</FileType>' + \
                             '<FilePath>' + back_path + 'example\\\\' + file + \
                             '\\\\source\\\\' + src1 + '</FilePath>' + \
                             '</File>' + os.linesep
    # parse driver c file
    c_src_file = ''
    
    #find c file
    dst_list = utils.find_inc(dir+ os.sep+'source'+os.sep + 'ddl_config.h')

    for dl in dst_list:
        dl = dl.lower()
        dl_series = DDL.SERIES.lower()
        dl =  dl_series + '_'+ dl
        for sl in g_driver_list:
            #if(dl == sl and 'gpio' != dl and 'clk' != dl and 'ddl' != dl):
            if(dl == sl and 'ddl' != dl):
                c_src_file += '<File>' + os.linesep + \
                        '<FileName>' + dl + '.c</FileName>' + os.linesep + \
                        '<FileType>1</FileType>' + \
                        '<FilePath>' + back_path + 'driver\\\\src\\\\' + \
                        dl + '.c' + '</FilePath>' + \
                        '</File>' + os.linesep
                break

    #driver_dir = os.path.join( DDL.DDL_DIR, 'driver')
    #if('gpio' != prj and 'clk' != prj and 'fgpio' != prj ):

    # eww parse midware c file
    mid_inc_file = ''
    mid_src_file = ''
    mid_flag = 0
    # find midware group
    mw_dst_list = utils.find_mid(dir + os.sep + 'source' + os.sep + 'ddl_config.h')

    for mdl in mw_dst_list:
        mdl = mdl.split('_')[0]
        mdl = mdl.lower()
        for msl in g_midware_list:
            if (msl == mdl):
                mid_flag += 1
                # add midware.h
                mid_inc_file += back_path + 'midware\\\\' + mdl + '\\\\inc' + ';'
                # add midware.c
                mid_src_list = os.listdir(DDL.DDL_MIDWARE_DIR + os.sep + mdl + os.sep + 'src')
                mid_src_file += '<Group>' + os.linesep + '    <GroupName>' + mdl + '</GroupName>' + os.linesep + \
                                '<Files>' + os.linesep
                for mid_src in mid_src_list:
                    mid_src_file += '<File>' + os.linesep + \
                                    '<FileName>' + mid_src + '</FileName>' + os.linesep + \
                                    '<FileType>1</FileType>' + os.linesep + \
                                    '<FilePath>' + back_path + 'midware\\\\' + mdl + '\\\\src\\\\' + \
                                    mid_src + '</FilePath>' + os.linesep + \
                                    '</File>' + os.linesep
                mid_src_file += '</Files>' + os.linesep + '</Group>' + os.linesep

    ################################
    ###  ETH & USB Project make
    cnt = 0
    flag = 0
    c_src_file1 = ''
    h_inc_file1 = ''
    SpcPoj_list = config.Prj_list
    Example_list = utils.find_example(DDL.CUR_DIR + os.sep + 'config.py')
    for poj in SpcPoj_list:
        if prj == poj:
            for exam in Example_list:
                if exam == file:
                    example_src_list = example_dict[prj + '_' + exam + '_source']
                    example_inc_list = example_dict[prj + '_' + exam + '_header']
                    for exa_src in example_src_list:
                        if exa_src.split('\\\\')[0] == 'driver':
                            c_src_file += '<File>' + os.linesep + \
                                          '<FileName>' + exa_src.split('\\\\')[-1] + '</FileName>' + os.linesep + \
                                          '<FileType>1</FileType>' +  '<FilePath>' + back_path  + \
                                          exa_src + '</FilePath>' +  '</File>' + os.linesep
                            continue
                        cnt += 1
                        if ('..' in exa_src) & ('....' not in exa_src):
                            exa_src = example_src_list[cnt - 2] + '\\\\' + example_src_list[cnt - 1]
                            exa_src = exa_src.replace('..', '')
                        if '....' in exa_src:
                            if '\\\\' not in example_src_list[cnt - 2]:
                                exa_src = example_src_list[cnt - 3].replace(example_src_list[cnt - 3].split('\\\\')[-1],
                                                                            '') + '\\\\' + example_src_list[cnt - 1]
                            else:
                                exa_src = example_src_list[cnt - 2].replace(example_src_list[cnt - 2].split('\\\\')[-1],
                                                                            '') + '\\\\' + example_src_list[cnt - 1]
                            exa_src = exa_src.replace('....', '')
                        # add midware.c
                        if flag == 0:
                            c_src_file1 += '<Group>' + os.linesep + '<GroupName>' + exa_src.split('\\\\')[1] + '</GroupName>' + os.linesep + \
                                        ' <Files>' + os.linesep
                            flag = 1
                        if os.path.isdir(DDL.DDL_DIR + '\\\\' + exa_src):
                            C_list = os.listdir(DDL.DDL_DIR + '\\\\' + exa_src)
                            for c_list in C_list:
                                if os.path.isdir(DDL.DDL_DIR + '\\\\' + exa_src + '\\\\' + c_list):
                                    continue
                                if c_list.split('.')[1] == 'c':
                                    c_src_file1 += '<File>' + os.linesep + \
                                                    '<FileName>' + c_list + '</FileName>' + os.linesep + \
                                                    '<FileType>1</FileType>' + os.linesep + \
                                                    '<FilePath>' + back_path + exa_src +'\\\\' +  c_list  + '</FilePath>' + os.linesep + \
                                                    '</File>' + os.linesep
                        else:
                            c_src_file1 += '<File>' + os.linesep + \
                                                    '<FileName>' + exa_src.split('\\\\')[-1] + '</FileName>' + os.linesep + \
                                                    '<FileType>1</FileType>' + os.linesep + \
                                                    '<FilePath>' + back_path + exa_src  + '</FilePath>' + os.linesep + \
                                                    '</File>' + os.linesep
                    for exa_inc in example_inc_list:
                        h_inc_file1 +=  back_path  + exa_inc  + ';'
                    c_src_file1 += '</Files>' + os.linesep + '</Group>' + os.linesep
                    buff_out = re.sub('<custom>{PROJ_MIDWARE_SRC}</custom>', c_src_file1, buff_out)

                    buff_out = re.sub('<custom>{PROJ_MIDWARE_INC}</custom>', h_inc_file1, buff_out)
#####################################
    # keil pash bsp c file
    bsp_inc_file = ''
    bsp_src_file = ''
    bsp_src = ''
    bsp_flag = 0
    # find bsp group
    bsp_dst_list = utils.find_bsp(dir + os.sep + 'source' + os.sep + 'ddl_config.h')
    for bsp in bsp_dst_list:
        bsp = bsp.lower()
        if bsp.split('_')[-1] == 'enable':
            bsp = bsp.split('_enable')[0]
        for bs in g_bsp_list:
            if bs == bsp:
                bsp_flag += 1
                if (bsp.split('_')[0] == 'ev') | (bsp.split('_')[0] == 'ms'):
                    # add bsp.h
                    bsp_inc_file += back_path + 'bsp\\\\' + bsp + ';'
                    # add bsp.c
                    bsp_src_file += '<Group>' + os.linesep + '<GroupName>' + bsp +'</GroupName>' + os.linesep + \
                                '<Files> ' + os.linesep

                    bsp_src_file += '<File>' + os.linesep + '<FileName>' + bsp + '.c'+ '</FileName>' + os.linesep + \
                                    '<FileType>1</FileType>' + os.linesep + '<FilePath>' + back_path + 'bsp\\\\' + \
                                    bsp +'\\\\' + bsp + '.c' '</FilePath>'+ '</File>' + '<custom>{bsp_src}</custom>'\
                                    + os.linesep
                    bsp_src_file += '</Files>' + os.linesep + '</Group>' + os.linesep
                else:
                    # add bsp.h
                    bsp_inc_file += back_path + 'bsp\\\\' + 'components\\\\' + bsp + ';'
                    # add bsp.c
                    bsp_src_file += '<Group>' + os.linesep + '<GroupName>' + bsp +'</GroupName>' + os.linesep + \
                                '<Files> ' + os.linesep
                    bsp_src_file += '<File>' + os.linesep + '<FileName>' + bsp + '.c' + '</FileName>' + os.linesep + \
                                        '<FileType>1</FileType>' + os.linesep + '<FilePath>' + back_path + 'bsp\\\\' + \
                                        'components\\\\' + bsp + '\\\\' + bsp + '.c' + '</FilePath>' + '</File>' + os.linesep
                    bsp_src_file += '</Files>' + os.linesep + '</Group>' + os.linesep
                if (bsp_flag > 1) & ((bsp_dst_list[0].split('_')[0] == 'EV') | (bsp_dst_list[0].split('_')[0] == 'MS')):
                    # add bsp.c
                    bsp_src_name = bsp_dst_list[0].lower() + '_' + bsp

                    bsp_src += '<File>' + os.linesep + '<FileName>' + bsp_src_name + '.c'+ '</FileName>' + os.linesep + \
                               '<FileType>1</FileType>' + os.linesep + '<FilePath>' + back_path + 'bsp\\\\' + \
                               bsp_dst_list[0].lower() + '\\\\' + bsp_src_name+ '.c' '</FilePath>'+ '</File>'+ os.linesep
    if (bsp_flag > 0):
        buff_out = re.sub('<custom>{PROJ_BSP_SRC}</custom>', bsp_src_file, buff_out)
        buff_out = re.sub('<custom>{PROJ_BSP_INC}</custom>', bsp_inc_file, buff_out)
        buff_out = re.sub('<custom>{bsp_src}</custom>', bsp_src, buff_out)
    else:
        buff_out = re.sub('<custom>{PROJ_BSP_INC}</custom>', '', buff_out)
        # add source c file except main.c
        src_path = os.path.join(dir, 'source')
        src_file_list = os.listdir(src_path)
        src_file_list = utils.find_c(src_file_list)
     #keil include path
    if(mid_flag>0):
        buff_out = re.sub('<custom>{PROJ_MIDWARE_INC}</custom>', mid_inc_file, buff_out)
        buff_out = re.sub('<custom>{PROJ_MIDWARE_SRC}</custom>', mid_src_file, buff_out)
    else:
        buff_out = re.sub('<custom>{PROJ_MIDWARE_INC}</custom>', '', buff_out)

    buff_out = re.sub('<custom>{PROJ_SRC}</custom>', src1_file, buff_out)
    ################
    buff_out = re.sub('{PERIPHERAL}',prj,buff_out)
    buff_out = re.sub('{FEATURE}',file,buff_out)
    buff_out = re.sub('{SAMPLE_DEPTH}',back_path,buff_out)
    buff_out = re.sub('{SFR_DEPTH}',sfr_path,buff_out)
    buff_out = re.sub('{PROJ_DRIVER_SRC}',c_src_file,buff_out)

    f1.write(buff_out.encode())
    f1.close()

    #rename uvoptx
    name1 = os.path.join(src,'ddl_template.uvoptx')
    name2 = os.path.join(src,file + '.uvoptx')
    os.rename(name1,name2)

    f1 = open(name2)
    buff_out = f1.read()
    f1.close()
    f1 = open(name2,'wb')
    buff_out = re.sub('{PERIPHERAL}',prj,buff_out)
    buff_out = re.sub('{FEATURE}',file,buff_out)
    f1.write(buff_out.encode())
    f1.close()

########################################################################
def make_project(rootdir,dir,f):
    str = []
    dir2 = dir.replace(rootdir+os.sep,'',1)

    str = dir2.rsplit('\\')
    str.reverse()
    str.pop(0) #remove source

    # feature module
    prj_name = str[0]
    if(len(str)> 1):
        prj_module = str[1]
        depth = 4
    else:
        prj_module = str[0]
        depth = 3

    #print prj_module , prj_name

    # make project 
    make_iar_project(rootdir,dir, prj_module,prj_name,depth)
    make_keil_project(rootdir,dir, prj_module,prj_name,depth)


def get_driver_list():
    mylist = []
    global g_driver_list
    f = ''
    for root,dirs,files in (os.walk(DDL.DDL_DRIVER_DIR)):
        for f in files:
            a =f.replace('.c','',1)
            mylist.append(a)


    g_driver_list = mylist

#get midware file list
def get_midware_list():
    global g_midware_list
    g_midware_list = os.listdir(DDL.DDL_MIDWARE_DIR)

#get bsp file list
def get_bap_list():
    global g_bsp_list
    mylist = []
    b = ''
    for root,dirs,files in (os.walk(DDL.DDL_BSP_DIR)):
        for f in files:
            a =f.split('.')[0]
            if a != b:
                mylist.append(a)
            b = a
    g_bsp_list = mylist

def get_SpecialProject_list():
    global g_usblib_list
    global g_usbctl_list
    g_usbctl_path = os.path.join(DDL.DDL_USBLIB_DIR, 'ctl_drv')
    g_usbctl_list = os.listdir(g_usbctl_path)
    g_usblib_list = os.listdir(DDL.DDL_USBLIB_DIR)



def make_examples(dir):

    if dir ==' ':
        dir = DDL.DDL_SAMPLE_DIR
    #find driver module list
    get_driver_list()
    #find midware module list
    get_midware_list()
    #find bsp module list
    get_bap_list()
    #print g_driver_list

    #check template folder exist
    for root,dirs, files in (os.walk(dir)):
        for f in files:
            str = root.split('\\')
            tpl = str[-2]
            #if('template' == tpl):
            #    break;

            name = os.path.split(f)[1]  #filename
            if 'main.c' == name.lower():
                
                #find a example, create project
                example_dir = root.replace('source','' ,1)
                copyFiles(TEMPLATE_SRC,example_dir)
                '''
                #move ddl_device.h to source
                src = os.path.join(example_dir,'ddl_device.h')
                dst = os.path.join(example_dir,'source')
                shutil.move(src,dst)
                '''
                #move ddl_board.h

                #make project
                make_project(DDL.DDL_SAMPLE_DIR,root,f)
                break

    return 0