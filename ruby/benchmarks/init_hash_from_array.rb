# encoding: utf-8

require 'benchmark'

header = 'Find out which hash init from array (val=0.0) method is the fastest'
functions = {
  'each_method' => 'histo = {}; values.each{|x| histo[x] = 0.0 }',
  'each_object_method' => 'values.each_with_object({}){|x, h| h[x] = 0.0 }',
  'each_object_method2' => 'values.each_with_object(0.0).to_h',
  'map_method' => 'values.map{|x| [x, 0.0] }.to_h',
  'inject_method' => 'values.inject({}){|h, x| h[x] = 0; h }',
  'inject_update_method' => 'values.inject({}){|h, x| h.update(x => 0.0) }',
  'zip_method' => 'values.zip([0.0] * values.size).to_h',
  'zip_method2' => 'values.zip(Array.new(values.size){0.0}).to_h',
}

def each_method(values)
  histo = {}
  values.each{|x| histo[x] = 0.0 }
  histo
end

def each_object_method(values)
  values.each_with_object({}){|x, h| h[x] = 0.0 }
end

def each_object_method2(values)
  values.each_with_object(0.0).to_h
end

def map_method(values)
  values.map{|x| [x, 0.0] }.to_h
end

def inject_method(values)
  values.inject({}){|h, x| h[x] = 0.0; h }
end

def inject_update_method(values)
  values.inject({}){|h, x| h.update(x => 0.0) }
end

def zip_method(values)
  values.zip([0.0] * values.size).to_h
end

def zip_method2(values)
  values.zip(Array.new(values.size){0.0}).to_h
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
sizes = (1..4).map{|x| 10**x }

sizes.each do |n|
  val = n.times.map{rand() }

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

# => Performance order: each >~ each_object > inject > map > ...
