#include "mounter.h"

#define INIT_SECTION_TEXT 0x08048000
#define INIT_SECTION_DATA 0x08049000


Mounter& Mounter::instance() {
	static Mounter m;
	return m;
}

void Mounter::mount(std::string foutname) {
	ELFIO::elfio writter;
	//writter.create(ELFCLASS32, ELFDATA2MSB); //big endian
	writter.create(ELFCLASS32, ELFDATA2LSB); //little endian
	writter.set_os_abi(ELFOSABI_LINUX);
	writter.set_type(ET_EXEC);
	writter.set_machine(EM_386);

	ELFIO::section* text_sec = writter.sections.add(".text");
	text_sec->set_type(SHT_PROGBITS);
	text_sec->set_flags(SHF_ALLOC | SHF_EXECINSTR);
	text_sec->set_addr_align(0x10);
	/*char text2[] =	 {'\xB8', '\x04', '\x00', '\x00', '\x00',  // mov eax, 4
					'\xBB', '\x01', '\x00', '\x00', '\x00',   // mov ebx, 1
					'\xB9', '\x20', '\x80', '\x04', '\x08',   // mov ecx, msg 
					'\xBA', '\x0E', '\x00', '\x00', '\x00',   // mov edx, 14 
					'\xCD', '\x80',                           // int 0x80
					'\xB8', '\x01', '\x00', '\x00', '\x00',   // mov eax, 1
					'\xCD', '\x80'};						  // int 0x80
	text_sec->set_data(text2, sizeof(text2));*/
	text_sec->set_data(text.c_str(), sizeof(text.c_str()));
	ELFIO::segment* text_seg = writter.segments.add();
	text_seg->set_type(PT_LOAD);
	text_seg->set_virtual_address(INIT_SECTION_TEXT);
	text_seg->set_physical_address(INIT_SECTION_TEXT);
	text_seg->set_flags(PF_X | PF_R);
	text_seg->set_align(0x1000);
	text_seg->add_section_index(text_sec->get_index(), text_sec->get_addr_align());

	ELFIO::section* data_sec = writter.sections.add(".data");
	data_sec->set_type(SHT_PROGBITS);
	data_sec->set_flags(SHF_ALLOC | SHF_WRITE);
	data_sec->set_addr_align(0x4);
	/*char data2[] = {	'\x48', '\x65', '\x6C', '\x6C', '\x6F',// “Hello, World!\n”
					'\x2C', '\x20', '\x57', '\x6F', '\x72',
					'\x6C', '\x64', '\x21', '\x0A'};
	data_sec->set_data(data2,sizeof(data2));*/
	data_sec->set_data(data.c_str(),sizeof(data.c_str()));
	ELFIO::segment* data_seg = writter.segments.add();
	data_seg->set_type(PT_LOAD);
	data_seg->set_virtual_address(INIT_SECTION_DATA);
	data_seg->set_physical_address(INIT_SECTION_DATA);
	data_seg->set_flags(PF_W | PF_R);
	data_seg->set_align(0x10);
	data_seg->add_section_index(data_sec->get_index(), data_sec->get_addr_align());

	writter.set_entry(0x08048000);
	writter.save(foutname);
	std::string temp = "chmod +x ./" + foutname;
	system(temp.c_str());
}