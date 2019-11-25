#include<idc.idc>

static getBaseAddr(ptr){
    return SegStart( ptr);
}

static printAddr(name , addr){
    Message("%s : 0x%x\n",name,addr);
}

static saveLastAddr(){
    auto nowPtr ;
    nowPtr = ScreenEA();
    auto base = getBaseAddr(nowPtr);
    printAddr("base",base);
    auto addr_offest = nowPtr - base;
    printAddr("offset",addr_offest);
    //nowPtr = nowPtr - base;
    auto fp = fopen("addr.log","w");
    auto code =  GetDisasm(nowPtr);
    auto addr_str = sprintf("0x%x",nowPtr);
    //savefile(fp,0,nowPtr,8);
    Message("save last addr-> %s : %s \n", addr_str,code);
    //Message(code);
    writelong(fp,addr_offest,0);
    writestr(fp , addr_str);
    writestr(fp , "\n");
    writestr(fp,code);

    fclose(fp);
}

static stepOverAndSave(){
    step_over();
    saveLastAddr();
}

static loadLastAddr(){
    auto nowPtr = ScreenEA();
    auto base  = getBaseAddr(nowPtr);
    printAddr("base",base);
    auto fp = fopen("addr.log","rb");
    auto offset_addr = readlong(fp,0);
    printAddr("offset_addr",offset_addr);
    auto addr = base + offset_addr;
    printAddr("addr",addr);

    //readstr(fp);
    auto addr_str = readstr(fp);
    //auto addr = sprintf("0x%s",addr_str);
    Message("load last addr: %s" +addr_str);
    auto code = readstr(fp);
    Message(code);
    Jump(addr);
    fclose(fp);
}

// static main()
// {
//     //saveLastAddr();
//     loadLastAddr();
//     return 0;
// }
