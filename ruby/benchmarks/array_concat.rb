# encoding: utf-8

require 'benchmark'

header = 'Find out which array concatenation method is the fastest'
functions = {
  'concat_method' => 'c = a.dup ; c.concat(b)',
  'append_method' => 'c = a.dup ; b.each{|x| c << x }',
  'push_method' => 'c = a.dup ; b.each{|x| c.push(x) }',
}

def concat_method(a, b)
  c = a.dup
  c.concat(b)
  c
end

def append_method(a, b)
  c = a.dup
  b.each{|x| c << x }
  c
end

def push_method(a, b)
  c = a.dup
  b.each{|x| c.push(x) }
  c
end

def check_equal_results(functions, a, b)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, a, b) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  v1 = n.times.map{rand(1000) }
  v2 = n.times.map{rand(1000) }

  # check equal results
  check_equal_results(functions, v1, v2)

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, v1, v2) } }
    end
  end
end

# => Performance order: concat >> append > push
