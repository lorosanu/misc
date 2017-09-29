# encoding: utf-8

require 'benchmark'

header = 'Find out which max method is the fastest'
functions = {
  'max_method' => 'values.max',
  'each_if_method' => 'values.each{|x| max = x if x > max }',
  'sort_method' => 'values.sort[-1]',
}

def max_method(values)
  values.max
end

def each_if_method(values)
  max = values[0]
  values.each{|x| max = x if x > max }
  max
end

def sort_method(values)
  values.sort[-1]
end

def check_equal_results(functions, values)
  res = []
  functions.each_key{|fname| res << self.__send__(fname, values) }

  raise "Functions generate different results: #{functions.keys.zip(res).to_h}"\
    unless res.uniq.size == 1
end

puts(header)
margin = functions.keys.map{|s| s.size }.max + 2
functions.each{|fname, desc| puts("#{fname.ljust(margin)} #{desc}") }

k = 1000
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  val = n.times.map{rand(1000) }

  # check equal results
  check_equal_results(functions, val)

  # launch benchmark
  puts("\n\nN=#{n}\n\n")
  Benchmark.bmbm do |b|
    functions.each_key do |fname|
      b.report(fname){k.times{self.__send__(fname, val) } }
    end
  end
end

# => Performance order: max >~ each_if >> sort
