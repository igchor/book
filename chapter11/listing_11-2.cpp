void leaf_node_t::insert(pool_base &pop,
			 const value_type &entry){
	auto insert_pos = v[current].size;

	entries[insert_pos] = entry;
	pop.flush(&(entries[insert_pos]),
		  sizeof(entries[insert_pos]));

	insert_idx(pop, insert_pos);
	pop.persist(&(v[1 - current]), sizeof(leaf_entries_t));

	current = 1 - current;
	pop.persist(&current, sizeof(current));
}

