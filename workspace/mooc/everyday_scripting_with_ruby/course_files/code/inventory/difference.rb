
old_inventory = File.open('old-inventory.txt').readlines
new_inventory = File.open('new-inventory.txt').readlines

files_added = new_inventory - old_inventory

puts "The Following #{files_added.length} files are added ... \n"
puts new_inventory - old_inventory
puts

files_removed = old_inventory - new_inventory

puts "The Following #{files_removed.length}  files are deleted ... \n"
puts old_inventory - new_inventory
puts

puts "Following files are unchanged... \n"
puts new_inventory - files_added
puts "--- OR ---"
puts old_inventory - files_removed.shuffle
puts "--- OR ---"
puts files_removed.shuffle

