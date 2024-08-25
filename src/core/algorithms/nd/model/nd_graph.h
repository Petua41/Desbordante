#pragma once

#include <map>
#include <set>
#include <vector>

#include "algorithms/nd/nd.h"
#include "model/table/column.h"
#include "model/table/vertical.h"

namespace model {

class NDGraph {
private:
    std::vector<model::ND> full_arcs_;
    std::set<Vertical> nodes_;
    std::set<Column> simple_nodes_;
    std::map<Vertical, std::vector<model::ND>> full_arcs_map_;
    std::multimap<Vertical, Column> dotted_arcs_;

public:
    /// @brief Create an ND-graph from a set of NDs
    NDGraph(std::vector<model::ND> const& delta) : full_arcs_(delta) {
        // Fill nodes_ and full_arcs_map_:
        for (auto const& full_arc : full_arcs_) {
            auto const& lhs = full_arc.GetLhs();
            auto const& rhs = full_arc.GetRhs();

            nodes_.insert(lhs);
            nodes_.insert(rhs);

            if (full_arcs_map_.find(lhs) == full_arcs_map_.end()) {
                std::vector<model::ND> vec{full_arc};
                full_arcs_map_.emplace(lhs, std::move(vec));
            } else {
                full_arcs_map_[lhs].push_back(full_arc);
            }
        }

        // Fill simple_nodes_:
        for (auto const& attrs : nodes_) {
            if (attrs.GetArity() > 1) {
                for (Column const* attr : attrs.GetColumns()) {
                    simple_nodes_.insert(*attr);
                    dotted_arcs_.emplace(attrs, *attr);
                }
            } else {
                simple_nodes_.insert(*(attrs.GetColumns().front()));
            }
        }
    }

    std::set<Vertical> const& Nodes() const {
        return nodes_;
    }

    std::set<Column> const& Attr() const {
        return simple_nodes_;
    }

    std::vector<model::ND> AllExtensions(Vertical const& node) const;

    std::vector<model::ND> AllExtensions(Column const& node) const;

    bool HasND(model::ND const& nd) const;
};

}  // namespace model
