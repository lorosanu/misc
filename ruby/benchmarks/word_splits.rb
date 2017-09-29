# encoding: utf-8

require 'benchmark'

header = 'Find out which word-split method is the fastest'
functions = {
  'while_method' => 'i = 0; while i <= val.size splits << ... end',
  'times_method' => '(val.size + 1).times{|i| splits << ... }',
  'each_map_method' => '(0..val.size).each.map{|i| [val[0...i], val[i..-1]] }',
}

def while_method(val)
  i = 0
  splits = []
  while i <= val.size
    splits << [val[0...i], val[i..-1]]
    i += 1
  end

  splits
end

def times_method(val)
  splits = []
  (val.size + 1).times{|i| splits << [val[0...i], val[i..-1]] }

  splits
end

def each_map_method(val)
  (0..val.size).each.map{|i| [val[0...i], val[i..-1]] }
end

def check_equal_results(functions, val)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, val) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 100000
words = %w[aye bonjour comment interrogation combinaison]
words.each do |word|
  # check equal results
  check_equal_results(functions, word)

  # launch benchmark
  puts("\n\nWord=#{word}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, word) } }
    end
  end
end

# => Performance order: while > times > each_map
