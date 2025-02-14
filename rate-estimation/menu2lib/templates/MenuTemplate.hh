#ifndef menulib_hh
#define menulib_hh

/* automatically generated from {{ menu.getName() }} with menu2lib.py */
/* https://github.com/cms-l1-dpg/L1MenuTools */

#include <string>
#include <vector>
#include <functional>
#include <map>

#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"

//
// common functions for algorithm implementations
//
/** re-calculate total-Ht with the given parameters
 *
 * @param upgrade [in] uGt inputs
 * @param max_eta [in] maximum abs(tower-IEta) to take into account for the sum
 * @param threshold [in] minimum tower energy to take into account for the sum
 * @return total-Ht
 */
double
get_total_ht(L1Analysis::L1AnalysisL1UpgradeDataFormat* upgrade,
             const int max_eta=28,
             const double threshold=30.);


/** compute transverse mass
 *
 * @param upgrade [in] uGt inputs
 * @param threshold_eg [in] minimum ET requirement for the leading-EG object
 * @param threshold [in] minimum missing-ET requirement
 * @return transverse mass. If Mt cannot be computed, -1.
 */
double
get_transverse_mass(L1Analysis::L1AnalysisL1UpgradeDataFormat* upgrade,
                    const double threshold_eg=30.,
                    const double threshold_met=30.);


// utility factories

class CombinationFactory
{
public:
  using data_t = std::vector<std::vector<size_t>>;
  using cache_t = std::map<std::pair<size_t, size_t>, data_t>;
  static const data_t& get(const size_t n, const size_t k);
  static void clear();
protected:
  static const data_t& insert(const size_t n, const size_t k);
private:
  static cache_t cache_;
};

class PermutationFactory
{
public:
  using data_t = std::vector<std::vector<size_t>>;
  using cache_t = std::map<size_t, data_t>;
  static const data_t& get(const size_t n);
  static void clear();
protected:
  static const data_t& insert(const size_t n);
private:
  static cache_t cache_;
};


// auxiliary functions
std::string getNameFromId(const int index);

int getIdFromName(const std::string& name);

typedef bool (*AlgorithmFunction)(L1Analysis::L1AnalysisL1UpgradeDataFormat*, L1Analysis::L1AnalysisL1CaloTowerDataFormat*);

AlgorithmFunction getFuncFromId(const int index);

AlgorithmFunction getFuncFromName(const std::string& name);

bool addFuncFromName(std::map<std::string, std::function<bool()>> &L1SeedFun,
                     L1Analysis::L1AnalysisL1UpgradeDataFormat* ntuple,
                     L1Analysis::L1AnalysisL1CaloTowerDataFormat* calo_tower);

// algorithms
{% for name, algo in menu.getAlgorithmMapPtr().items() %}
bool
{{ name }}(L1Analysis::L1AnalysisL1UpgradeDataFormat*, L1Analysis::L1AnalysisL1CaloTowerDataFormat*);
{% endfor %}


{#
 # jinja templates
 #}
{% set scaleMap = menu.getScaleMapPtr() %}

// generate scales
{% include 'Scales.jinja2' %}

// generate LUTs
{% include 'CaloCaloLUT.jinja2' %}
{% include 'CaloEsumLUT.jinja2' %}
{% include 'CaloMuonLUT.jinja2' %}
{% include 'MuonEsumLUT.jinja2' %}
{% include 'MuonMuonLUT.jinja2' %}

#endif // menulib_hh
// eof
