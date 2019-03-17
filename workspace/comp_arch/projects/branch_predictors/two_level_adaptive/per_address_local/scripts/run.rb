# Per Address Local History

require 'uuid'

###########################
#                         #
# PREDICTOR CONFIGURATION #
#                         #
###########################

# Return Address Stack 
RAT_SIZE = [32]

# Global History Size
G_HIST_SIZE = [16]

# Associative History Register Size
AHRT_SIZE = [256, 512, 1024, 2048, 4096, 8192, 16382, 32768]

# AHRT Associativity
AHRT_ASSO = [4]

# BRANCH TARGET BUFFER 
BTB_SIZE = [16384]

CONFIGURATION = { "RAT_SIZE"    => RAT_SIZE,
                  "G_HIST_SIZE" => G_HIST_SIZE, 
                  "AHRT_SIZE"   => AHRT_SIZE, 
                  "AHRT_ASSO"   => AHRT_ASSO, 
                  "BTB_SIZE"    => BTB_SIZE }

puts "\n"
puts "********************************"
puts "* BRANCH PREDICTIOR SIMULATION *"
puts "********************************"
puts "\n"

puts "--- Test Configurations---\n"
CONFIGURATION.each do |key, value| puts "#{key} = #{value}" end
puts "--------------------------"

FNAME = UUID.new.generate
RESULTS_FOLDER = "../results/per_address/#{FNAME}"
system("mkdir -p #{RESULTS_FOLDER}")

PREDICTOR_PATH = "../src/"
TRACES_PATH = "../traces"

log_file = File.new("#{RESULTS_FOLDER}/results.log", "w")

trace_list = Dir.glob("#{TRACES_PATH}/*").sort.map! do |trace| 
  File.basename(trace, ".*")
end

num_configs = 1
CONFIGURATION.each do |key,value| 
  num_configs = num_configs * value.length
end

x = 0
CONFIGURATION["RAT_SIZE"].each do |rat_size|
  CONFIGURATION["G_HIST_SIZE"].each do |g_hist_size|
    CONFIGURATION["AHRT_SIZE"].each do |ahrt_size|
      CONFIGURATION["AHRT_ASSO"].each do |ahrt_asso|
        CONFIGURATION["BTB_SIZE"].each do |btb_size|
          x = x + 1 
          puts "Config #{x}: RAT_SIZE = #{rat_size} G_HIST_SIZE = #{g_hist_size} AHRT_SIZE = #{ahrt_size} AHRT_ASSO = #{ahrt_asso} BTB_SIZE = #{btb_size} "
        end
      end
    end
  end
end

