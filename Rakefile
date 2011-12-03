require 'rake/clean'

#utility functions
module Enumerable
	def replace_dir_and_ext(dir, ext)
		self.collect{|x| x.replace_dir_and_ext(dir, ext)}
	end
	
	def replace_dir_and_remove_ext(dir)
		self.collect{|x| x.replace_dir_and_remove_ext(dir)}
	end
	
	def quote
	  self.collect{|x| x.quote}
	end
end

class String
	def replace_dir_and_ext(dir, ext)
		file_name = File.basename(self).split(".")[0]
		
		dir + '/' + file_name + '.' + ext
	end
	
	def replace_dir_and_remove_ext(dir)
		file_name = File.basename(self).split(".")[0]
			
		dir + '/' + file_name
	end
	
	def replace_dir(dir)
	  file_name = File.basename(self)
			
		dir + '/' + file_name
	end
	
	def quote
	  "\"#{self}\""
	end
end

class FileList
  include Enumerable
end

#directories
ROOT_DIR  = File.expand_path(File.dirname(__FILE__))
SRC_DIR   = ROOT_DIR + '/src'
OBJ_DIR   = ROOT_DIR + '/obj'
LIB_DIR   = ROOT_DIR + '/lib'
TESTS_DIR = ROOT_DIR + '/tests'
BIN_DIR   = ROOT_DIR + '/bin'


#file collections
SRCS      = FileList["#{SRC_DIR}/*.cpp"]
OBJS      = SRCS.replace_dir_and_ext(OBJ_DIR, 'o')
LIB		    = LIB_DIR + "/libbitstring.a"
TEST_SRCS = FileList["#{TESTS_DIR}/*.cpp"]
TESTS     = TEST_SRCS.replace_dir_and_remove_ext(BIN_DIR)

CC = 'g++ -ggdb'
LINKER = 'ld'
LIBRARIAN = 'ar'

CLEAN.include(OBJ_DIR + "/*.o")
CLEAN.include(LIB)
CLEAN.include(BIN_DIR + "/*")

task :default => TESTS

TESTS.each{|test| 
  test_src = (TESTS_DIR + '/' + File.basename(test) + ".cpp") 
  test_obj = (OBJ_DIR + '/' + File.basename(test) + ".o") 

  file test => [test_obj, LIB] do
    test_path = make(test_obj, LIB, BIN_DIR)
  	system("\"#{test}\"")
  end
  
  file test_obj => test_src do
		compile_entry_point(test_src, test_obj)
  end
  
  system("\"#{test}\"") if File.exist?(test)
}


task :build => LIB

file LIB => OBJS do
	link(OBJS, LIB)
end

OBJS.each do |obj_file|
	src_file = obj_file.replace_dir_and_ext(SRC_DIR, 'cpp')
	file obj_file => src_file do 
		compile(src_file, obj_file)
	end
end

#actions

def make(test_obj, lib_path, bin_dir)
	lib_dir       = File.dirname(lib_path)
	lib_file_name = File.basename(lib_path, '.a')
	lib_name      = lib_file_name[3..-1]
	output_path   = bin_dir +'/' + File.basename(test_obj, '.o')
	cmd           = "#{LINKER} -o \"#{output_path}\" /usr/lib/crt1.o \"#{test_obj}\" -L\"#{lib_dir}\"  -lc -lstdc++.6 -l#{lib_name}"
	system(cmd)
end

def link(objs, lib_path)
	cmd = "#{LIBRARIAN} -r \"#{lib_path}\" #{objs.quote.join(" ")}"
	system(cmd)
end

def compile_entry_point(src_path, obj_path)
  cmd = "#{CC} -c \"#{src_path}\" -o \"#{obj_path}\""
	system(cmd)
end

def compile(src_path, obj_path)
	cmd = "#{CC} -c \"#{src_path}\" -o \"#{obj_path}\""
	system(cmd)
end












