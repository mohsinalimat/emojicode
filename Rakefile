# Sorry to embarrass you, but this file simply runs gcc commands.
require 'fileutils'

cc = 'gcc'
flags = '-Ofast -iquote . -iquote Emojicode/ -iquote EmojicodeCompiler '\
        '-std=gnu11 -Wno-unused-result -lm -ldl -g -rdynamic'
pkg_flags = '-O3 -iquote . -std=c11 -Wno-unused-result -shared -fPIC -g'

pkg_flags += ' -undefined dynamic_lookup' if RUBY_PLATFORM.match(/darwin/)

destination = "builds/#{`#{cc} #{flags} -dumpmachine`.strip}"
FileUtils.mkdir_p destination

task default: :build

desc 'Packages builds for shipment'
task package: :build do
  headers = File.join(destination, 'headers')
  install = File.join(destination, 'install.sh')
  FileUtils.rm_r headers if File.directory? headers
  FileUtils.cp_r 'headers', headers
  FileUtils.rm install if File.exist? install
  FileUtils.cp 'install.sh', install
  basename = File.basename(destination)
  `tar -czf builds/#{basename}.tar.gz -C builds #{basename}`
end

desc 'Builds the compiler and the engine'
task build: [:engine, :compiler, :files_pkg, :SDL_pkg, :sqlite_pkg]

desc 'Builds the engine'
task :engine do
  sh "#{cc} Emojicode/*.c -o #{destination}/emojicode #{flags}"
end

desc 'Builds the compiler'
task :compiler do
  sh "#{cc} Emojicode/utf8.c EmojicodeCompiler/*.c -o "\
      "#{destination}/emojicodec #{flags}"
end

desc 'Builds a package'
rule(/_pkg$/) do |t|
  name = t.name.chomp '_pkg'
  sh "#{cc} DefaultPackages/#{name}/*.c -o"\
      "#{destination}/#{name}.so #{pkg_flags}"
end

desc 'Builds the SDL Package'
task :SDL_pkg do |t|
  name = t.name.chomp '_pkg'
  sh "#{cc} DefaultPackages/#{name}/*.c -o"\
      "#{destination}/#{name}.so #{pkg_flags} -lSDL2"
end
