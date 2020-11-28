from .bindings import get_cpu_info
import pprint

__all__ = ['CPUInfo']

class FeatureFalgs(dict):
    def __init__(self, *args, **kwargs):
        super(FeatureFalgs, self).__init__(*args, **kwargs)
        self.__dict__ = self

class CPUInfo():

    def __init__(self):

        #load cpu info
        self.cpu_info = get_cpu_info()
        self.features = FeatureFalgs(self.cpu_info.features.items())
    
    def as_dict(self, include_features = True):
        
        info_dict = {}
        for _attr in dir(self.cpu_info):
            if _attr == "features":
                if not include_features :
                    continue
                info_dict['features'] = self.features
            elif not _attr.startswith("_"):
                info_dict[_attr] = getattr(self.cpu_info, _attr)
        
        return info_dict
    
    def get_info_fields(self) :

        info_fields = []
        for _attr in dir(self.cpu_info):
            if not _attr.startswith("_"):
                info_fields.append(_attr)

        return info_fields        
    
    def pprint(self):
        dict_type = self.as_dict()
        pprint.pprint(dict_type)
    
    def get_features(self):
        return self.features
    
    def get_features_as_dict(self):
        return dict(self.features)
    
    def print_as_table(self):
        
        print("CPU Description:")
        print("--------------------------------------")
        print("{:<15} {:<10}".format('Label','Value'))
        print("--------------------------------------")
        for _att in dir(self.cpu_info):
            if _att.startswith("_") or _att == "features":
                continue
            print("{:<15} {:<10}".format(_att, getattr(self.cpu_info, _att)))
        
        print("\nCPU Features:")
        print("--------------------------------------------------------")
        print("{:<30} {:<20}".format('Feature Name', 'Is supported?'))
        print("--------------------------------------------------------")
        for key, value in sorted(self.features.items()):
            print("{:<30} {:<20}".format(key, "Yes" if value else "No"))
    
    def __getitem__(self, attr):
        return getattr(self.cpu_info, attr)