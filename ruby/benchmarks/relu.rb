# encoding: utf-8

require 'benchmark'

header = 'Find out which relu method is the fastest'
functions = {
  'times_if_method' => 'values.size.times{|i| values[i] = 0 if values[i] < 0 }',
  'map_conditional_method' => 'values.map{|x| x > 0 ? x : 0 }',
  'map_max_method' => 'values.map{|x| [0, x].max }',
}

def times_if_method(values)
  values.size.times{|i| values[i] = 0 if values[i] < 0 }
  values
end

def map_conditional_method(values)
  values.map{|x| x > 0 ? x : 0 }
end

def map_max_method(values)
  values.map{|x| [0, x].max }
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
sizes = (1..5).map{|x| 10**x }

sizes.each do |n|
  val = n.times.map{rand() - rand() }

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

# => Performance order: times_if > map_contitional >> map_max
