# encoding: utf-8

require 'benchmark'
require 'unf'
require 'unicode'
require 'unicode_utils'

# ruby's downcase does not work well on unicode for ruby versions < 2.4

header = 'Find out which unicode downcase method is fastest'
functions = {
  'unf_downcase_method' => 's.to_nfd.downcase.to_nfc',
  'unicode_downcase_method' => 'Unicode.downcase(s)',
  'unicode_utils_downcase_method' => 'UnicodeUtils.downcase(s)',
}

def unf_downcase_method(text)
  text.to_nfd.downcase.to_nfc
end

def unicode_downcase_method(text)
  Unicode.downcase(text)
end

def unicode_utils_downcase_method(text)
  UnicodeUtils.downcase(text)
end

def check_equal_results(functions, v)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, v) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000

letters = ('a'..'z').to_a
letters.concat(('A'..'Z').to_a)
letters.concat(%w[ç é â ê î ô û à è ù ë ï ü])
letters.concat(%w[Ç É Â Ê Î Ô Û À È Ù Ë Ï Ü])
letters << ' '

sizes = (1..5).map{|x| 10**x }
sizes.each do |n|
  text = n.times.map{letters.sample(1)[0] }.join('')

  # check equal results
  check_equal_results(functions, text)

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, text) } }
    end
  end
end

# => Performance order: unf > unicode >> unicode_utils
